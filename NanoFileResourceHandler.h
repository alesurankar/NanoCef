#pragma once
#include "Include/cef_resource_handler.h"
#include "Include/cef_parser.h"
#include <fstream>
#include <string>
#include <filesystem>

class NanoFileResourceHandler : public CefResourceHandler
{
public:
	bool Open(
		CefRefPtr<CefRequest> request,
		bool& handleRequest,
		CefRefPtr<CefCallback> pCallback) override
	{
		handleRequest = true;

		CefURLParts urlParts;
		if (!CefParseURL(request->GetURL(), urlParts)) 
		{
			MessageBoxA(nullptr, "Invalid URL in request.", "Request Error", MB_ICONERROR);
			return false;
		}

		try 
		{
			const std::string rawPath = CefString(&urlParts.path);
			if (rawPath.empty()) 
			{
				MessageBoxA(nullptr, "Empty request path.", "Request Error", MB_ICONERROR);
				return false;
			}

			// Sanitize and resolve path
			auto path = std::filesystem::path{ rawPath }.lexically_normal().relative_path();
			const std::filesystem::path rootDir = "webroot";
			const std::filesystem::path fullPath = std::filesystem::weakly_canonical(rootDir / path);

			// Restrict to webroot directory
			if (fullPath.string().find(std::filesystem::canonical(rootDir).string()) != 0) 
			{
				MessageBoxA(nullptr, "Blocked path traversal attempt.", "Security Warning", MB_ICONWARNING);
				return false;
			}

			// Verify file exists and is regular file
			if (!std::filesystem::exists(fullPath) || !std::filesystem::is_regular_file(fullPath)) 
			{
				MessageBoxA(nullptr, ("File not found:\n" + fullPath.string()).c_str(), "Request Error", MB_ICONERROR);
				return false;
			}

			// Store size and MIME type
			fileSize_ = (int64_t)std::filesystem::file_size(fullPath);
			auto ext = fullPath.extension().string();
			ext.erase(std::remove(ext.begin(), ext.end(), '.'), ext.end());

			if (!ext.empty())
			{
				fileMimeType_ = CefGetMimeType(ext);
			}

			// Open file stream
			fileStream_ = std::ifstream{ fullPath, std::ios::binary };
			if (!fileStream_.is_open()) 
			{
				MessageBoxA(nullptr, ("Failed to open file:\n" + fullPath.string()).c_str(), "File Error", MB_ICONERROR);
				return false;
			}
			return true;
		}
		catch (const std::exception& ex)
		{
			std::string message = "Request failed:\n";
			message += ex.what();
			MessageBoxA(nullptr, message.c_str(), "Exception Caught", MB_ICONERROR);
			return false;
		}
	}
	void GetResponseHeaders(
		CefRefPtr<CefResponse> pResponse,
		int64_t& responseLength,
		CefString& redirectUrl) override
	{
		if(!fileMimeType_.empty())
		{
			pResponse->SetMimeType(fileMimeType_);
		}
		pResponse->SetStatus(200);
		responseLength = fileSize_;
	}
	void Cancel() override {}
	bool Read(
		void* dataOut,
		int bytesToRead,
		int& bytesRead,
		CefRefPtr<CefResourceReadCallback> pCallback) override
	{
		//if we don't have an out buffer, that's a problem
		if(!dataOut) 
		{
			bytesRead = -2;
			return false;
		}
		//attempt to read up to bytesToRead
		fileStream_.read(static_cast<char*>(dataOut), bytesToRead);

		//gcout() is how many bytes we actually got during the last read
		bytesRead = (int)fileStream_.gcount();

		// if we got *any* bytes, return true
		// (returning false with bytesRead==0 signals EOF to CEF)
		return bytesRead > 0;
	}
private:
	std::ifstream fileStream_;
	int64_t fileSize_ = 0;
	std::string fileMimeType_;
	IMPLEMENT_REFCOUNTING(NanoFileResourceHandler);
};
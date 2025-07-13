<script setup lang="ts">

</script>
<template>
  <v-app>
    <v-app-bar app style="-webkit-app-region: drag; user-select: none;">
      <v-toolbar-title>My App</v-toolbar-title>
      <v-btn icon style="-webkit-app-region: no-drag;">
        <v-icon>mdi-content-cut</v-icon>
      </v-btn>
      <v-btn icon style="-webkit-app-region: no-drag;">
        <v-icon color="red">mdi-axis-arrow-lock</v-icon>
      </v-btn>
      <v-spacer />
      <v-btn icon class="rounded-0" style="width: 40px; height: 40px; -webkit-app-region: no-drag;">
        <v-icon>mdi-window-minimize</v-icon>
      </v-btn>
      <v-btn icon style="-webkit-app-region: no-drag;">
        <v-icon>mdi-window-minimize</v-icon>
      </v-btn>
      <v-btn icon style="-webkit-app-region: no-drag;">
        <v-icon>mdi-window-maximize</v-icon>
      </v-btn>
      <v-btn icon style="-webkit-app-region: no-drag;">
        <v-icon>mdi-close</v-icon>
      </v-btn>
    </v-app-bar>

    <v-main>
      <v-container fluid class="d-flex pa-0" style="height: calc(80vh - 48px - 32px);">
        <div style="width: 220px; background-color: #1e1e1e;">
          <v-toolbar flat density="compact">
            <v-toolbar-title class="text-white">Navigation</v-toolbar-title>
          </v-toolbar>
          <v-divider></v-divider>
          <v-btn block to="/">Home</v-btn>
          <v-btn block to="/cart">Cart</v-btn>
          <v-btn block to="/sds">Spacer_divider_sheet</v-btn>
        </div>
        <div class="flex-grow-1 pa-4">
          <router-view />
        </div>
      </v-container>
    </v-main>

    <v-footer app>
      <span>&copy; 2025</span>
    </v-footer>
  </v-app>
</template>

<style scoped>
.price
{
  font-size: 20px;
  font-weight: bold;
  padding-right: 20px;
}
</style>
<script setup lang="ts">
import { ref } from 'vue'
const darkMode = ref(false)
</script>

<template>
  <v-app :theme="darkMode ? 'dark' : 'light'">
    <v-main>
      <v-container width="800">
        <v-card class="mb-3 py-2 px-3">
          <p>blablabla, blablablablablabla, blablablablablabla, blablablablablabla, blablabla. Bblablabla, blablablablablabla, blablabla</p>
          <p>Hahaha, ha,hahaHahaha, ha,haha,Hahaha, ha,hahaHahaha, ha,haha. Hahaha, ha,hahaHahaha, ha,haha</p>
        </v-card>
        <v-card class="mb-3 py-2 px-3">
          <p>juhuhuhu, juhu juhuhu, juhuhu. Juhuhuhu, juhu juhuhu, juhuhujuhuhuhu, juhu juhuhu, juhuhu, juhuhuhu, juhu juhuhu, juhuhu. Jjuhuhuhu, juhu juhuhu, juhuhu</p>
        </v-card>
        <v-switch 
          v-model="darkMode"
          label="Dark Mode">
        </v-switch>
      </v-container>
    </v-main>
  </v-app>
</template>

<style scoped>
</style>
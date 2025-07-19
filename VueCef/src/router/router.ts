// src/router.ts or router/index.ts
import { createRouter, createWebHistory } from 'vue-router'

import Home from '../views/Home.vue'
import Chart from '../views/Chart.vue'
import Dice_roll_simulator from '../views/dice_roll_simulator.vue'

const routes = [
  { path: '/', component: Home },
  { path: '/chart', component: Chart },
  { path: '/drs', component: Dice_roll_simulator }
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

export default router

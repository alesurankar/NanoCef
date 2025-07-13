// src/router.ts or router/index.ts
import { createRouter, createWebHistory } from 'vue-router'

import Home from '../views/Home.vue'
import Cart from '../views/Cart.vue'
import Spacer_divider_sheet from '../views/Spacer_divider_sheet.vue'

const routes = [
  { path: '/', component: Home },
  { path: '/cart', component: Cart },
  { path: '/sds', component: Spacer_divider_sheet }
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

export default router

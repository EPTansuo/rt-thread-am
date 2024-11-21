#include <am.h>
#include <klib.h>
#include <rtthread.h>

static rt_ubase_t from_g,to_g;

static Context *ev_handler(Event ev, Context *c)
{
  switch (ev.event)
  {
    case EVENT_YIELD:
    {
      Context **from = (Context **)from_g;
      Context **to = (Context **)to_g;
      if (from != NULL)
        *from = c;
      c = *to;
      break;
    }
    default:
      printf("Unhandled event: ID = %d\n", ev.event);
      assert(0);
  }
  return c;
}

void __am_cte_init()
{
  cte_init(ev_handler);
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
{
  from_g = from;
  to_g = to;
  yield();

}


void rt_hw_context_switch_to(rt_ubase_t to)
{
  //assert(0);
  rt_hw_context_switch(0, to);
}


void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread)
{
   assert(0);
  return;
}

static void tentry_entry(void *parameter) {
  uintptr_t *args = parameter;
  void (*tentry)() = (void*)args[1];
  tentry(args[0]);
  void (*texit)() = (void*)args[2];
  texit(); 
}

// 参考：https://riscv-rtthread-programming-manual.readthedocs.io/zh-cn/latest/zh_CN/8.html
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
  rt_uint8_t         *stk;

  stk  = stack_addr + sizeof(rt_ubase_t);
  stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, sizeof(rt_ubase_t));

  uintptr_t *args = (void*)(stk-3*sizeof(uintptr_t));
  stk -= 3*sizeof(uintptr_t);
  
  args[0]=(uintptr_t)parameter;
  args[1]=(uintptr_t)tentry;
  args[2]=(uintptr_t)texit;
  
  Context* c = kcontext((Area){0, stk}, tentry_entry, args);

  return (rt_uint8_t*)c;
}

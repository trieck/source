#include "ruby.h"
#include "queue.h"

VALUE cQueue;

static void queue_free(void *p) 
{
	qfree(p);
}

static VALUE queue_new(VALUE class)
{
	struct queue *ptr = qalloc();
	VALUE tdata = Data_Wrap_Struct(class, 0, queue_free, ptr);
	rb_obj_call_init(tdata, 0, NULL);
	return tdata;
}

static VALUE queue_init(VALUE self)
{
	return self;
}

static VALUE queue_put(VALUE self, VALUE obj)
{
	struct queue *ptr;
	void *value;
	
	Data_Get_Struct(self, struct queue, ptr);
	Data_Get_Struct(obj, void, value);

	qput(ptr, value);
	
	return self;
}

static VALUE queue_get(VALUE self)
{
	struct queue *ptr;
	void *value;
	VALUE tdata;
	
	Data_Get_Struct(self, struct queue, ptr);
	value = qget(ptr);
	
	// tdata = Data_Wrap_Struct(klass, 0, 0, value)
	
	return tdata;
}

void Init_Queue()
{
	cQueue = rb_define_class("Queue", rb_cObject);
	rb_define_singleton_method(cQueue, "new", queue_new, 0);
	rb_define_method(cQueue, "initialize", queue_init, 0);
	rb_define_method(cQueue, "put", queue_put, 1);
	rb_define_method(cQueue, "get", queue_get, 0);
}

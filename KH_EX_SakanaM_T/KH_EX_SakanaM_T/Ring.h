
#pragma once

template<class T>
class Ring
{	public:
	Ring() {}

	void
	Add_new_node(T* d)
	{
		Ring* r = new Ring;
		r->data = d;
		r->next = next;
		r->last = this;
		next->last = r;
		next = r;
	}

	void
	Out_and_delete_this()
	{
		next->last = last;
		last->next = next;
	
		delete data;
		delete this;
	}

	Ring* Get_next() { return next; }
	Ring* Get_last() { return last; }

	T* Get_data() { return data; }

	inline static void
	Delete_all_but(Ring* r)
	{
		Ring* nn = nullptr;
		Ring* n = r->next;
		while (n != r)
		{
			nn = n->next;
			delete n->data;
			delete n;
			n = nn;
		}
	}

	inline static void
	Run_all(Ring* ring, bool(T::*f)())
	{
		Ring* lst = nullptr;
		Ring* now = ring->Get_next();
		while (now != ring)
		{
			lst = now;
			now = now->next;
			if (!(lst->data->*f)())
			{
				lst->Out_and_delete_this();
			}
		}
	}

private:

	Ring* next = this;
	Ring* last = this;

	T* data = nullptr;
};

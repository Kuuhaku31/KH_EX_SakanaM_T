
#pragma once

template<class T>
class Ring
{	public:
	Ring() {}


	Ring* Get_next() { return next; }
	Ring* Get_last() { return last; }

	T* Get_data() { return data; }

	void
	Add_new_node(T* d)
	{
		Ring* r = new Ring;
		r->next = next;
		r->last = this;
		r->data = d;

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

	void
	Add_ring_but_head(Ring* ring)
	{
		if (ring->next != ring)
		{
			ring->next->last = this;
			ring->last->next = next;

			next->last = ring->last;
			next = ring->next;

			ring->next = ring->last = ring;
		}
	}

	void
	Delete_all_but_this()
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			delete lst->data;
			delete lst;
		}
	}

	void
	Run_all_but_this_to_update()
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			if (!lst->data->T::Update())
			{
				lst->last->next = now;
				now->last = lst->last;
				delete lst->data;
				delete lst;
			}
		}
	}

	void
	Run_all_but_this_to_do(void(T::* f)())
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			(lst->data->*f)();
		}
	}

	void
	Run_all_but_this_to_add(T* (T::* f)())
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			T* d = (lst->data->*f)();
			if (d)
			{
				Ring* r = new Ring;
				r->data = d;
				r->next = now;
				r->last = lst;
				now->last = r;
				lst->next = r;
				now = r;
			}
		}
	}

	void
	Run_all_but_this_to_delete(bool(T::* fA)(), void(T::* fB)())
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			if (!(lst->data->*fA)())
			{
				lst->next->last = lst->last;
				lst->last->next = lst->next;

  				(lst->data->*fB)();
				delete lst->data;
				delete lst;
			}
		}
	}

private:

	Ring* next = this;
	Ring* last = this;

	T* data = nullptr;
};

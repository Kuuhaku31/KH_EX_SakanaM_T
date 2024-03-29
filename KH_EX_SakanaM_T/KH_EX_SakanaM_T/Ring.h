
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
	Run_all_but_this_to_delete(bool(T::* f)())
	{
		Ring* lst = nullptr;
		Ring* now = this->next;
		while (now != this)
		{
			lst = now;
			now = now->next;
			if (!(lst->data->*f)())
			{
				lst->next->last = lst->last;
				lst->last->next = lst->next;

				delete data;
				delete lst;
			}
		}
	}

private:

	Ring* next = this;
	Ring* last = this;

	T* data = nullptr;
};

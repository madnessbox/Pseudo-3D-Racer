#pragma once
template<class T, class TOther>
bool IsA(TOther* Ptr)
{
	T* TPtr = dynamic_cast<T*>(Ptr);
	return TPtr != nullptr;
}
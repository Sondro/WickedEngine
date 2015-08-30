#include "Vector_BindLua.h"
#include "Matrix_BindLua.h"

using namespace DirectX;


const char Vector_BindLua::className[] = "Vector";

Luna<Vector_BindLua>::FunctionType Vector_BindLua::methods[] = {
	lunamethod(Vector_BindLua, GetX),
	lunamethod(Vector_BindLua, GetY),
	lunamethod(Vector_BindLua, GetZ),
	lunamethod(Vector_BindLua, GetW),
	lunamethod(Vector_BindLua, SetX),
	lunamethod(Vector_BindLua, SetY),
	lunamethod(Vector_BindLua, SetZ),
	lunamethod(Vector_BindLua, SetW),
	lunamethod(Vector_BindLua, Transform),
	{ NULL, NULL }
};
Luna<Vector_BindLua>::PropertyType Vector_BindLua::properties[] = {
	{ NULL, NULL }
};

Vector_BindLua::Vector_BindLua(const XMVECTOR& vector) : vector(vector)
{
}

Vector_BindLua::Vector_BindLua(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	float x = 0.f, y = 0.f, z = 0.f, w = 0.f;

	if (argc > 0)
	{
		x = wiLua::SGetFloat(L, 1);
		if (argc > 1)
		{
			y = wiLua::SGetFloat(L, 2);
			if (argc > 2)
			{
				z = wiLua::SGetFloat(L, 3);
				if (argc > 3)
				{
					w = wiLua::SGetFloat(L, 4);
				}
			}
		}
	}
	vector = XMVectorSet(x, y, z, w);
}

Vector_BindLua::~Vector_BindLua()
{
}


int Vector_BindLua::GetX(lua_State* L)
{
	wiLua::SSetFloat(L, XMVectorGetX(vector));
	return 1;
}
int Vector_BindLua::GetY(lua_State* L)
{
	wiLua::SSetFloat(L, XMVectorGetY(vector));
	return 1;
}
int Vector_BindLua::GetZ(lua_State* L)
{
	wiLua::SSetFloat(L, XMVectorGetZ(vector));
	return 1;
}
int Vector_BindLua::GetW(lua_State* L)
{
	wiLua::SSetFloat(L, XMVectorGetW(vector));
	return 1;
}

int Vector_BindLua::SetX(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		vector = XMVectorSetX(vector, wiLua::SGetFloat(L, 2));
	}
	else
		wiLua::SError(L, "SetX(float value) not enough arguments!");
	return 0;
}
int Vector_BindLua::SetY(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		vector = XMVectorSetY(vector, wiLua::SGetFloat(L, 2));
	}
	else
		wiLua::SError(L, "SetY(float value) not enough arguments!");
	return 0;
}
int Vector_BindLua::SetZ(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		vector = XMVectorSetZ(vector, wiLua::SGetFloat(L, 2));
	}
	else
		wiLua::SError(L, "SetZ(float value) not enough arguments!");
	return 0;
}
int Vector_BindLua::SetW(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		vector = XMVectorSetW(vector, wiLua::SGetFloat(L, 2));
	}
	else
		wiLua::SError(L, "SetW(float value) not enough arguments!");
	return 0;
}

int Vector_BindLua::Transform(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Matrix_BindLua* mat = Luna<Matrix_BindLua>::lightcheck(L, 2);
		if (mat)
		{
			vector = XMVector4Transform(vector, mat->matrix);
		}
		else
			wiLua::SError(L, "Transform(Matrix matrix) argument is not a Matrix!");
	}
	else
		wiLua::SError(L, "Transform(Matrix matrix) not enough arguments!");
	return 0;
}


int Vector_BindLua::Dot(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Vector_BindLua* v1 = Luna<Vector_BindLua>::lightcheck(L, 1);
		Vector_BindLua* v2 = Luna<Vector_BindLua>::lightcheck(L, 2);
		if (v1 && v2)
		{
			Luna<Vector_BindLua>::push(L, new Vector_BindLua(XMVector3Dot(v1->vector,v2->vector)));
			return 1;
		}
	}
	wiLua::SError(L, "VectorDot(Vector v1,v2) not enough arguments!");
	return 0;
}
int Vector_BindLua::Cross(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Vector_BindLua* v1 = Luna<Vector_BindLua>::lightcheck(L, 1);
		Vector_BindLua* v2 = Luna<Vector_BindLua>::lightcheck(L, 2);
		if (v1 && v2)
		{
			Luna<Vector_BindLua>::push(L, new Vector_BindLua(XMVector3Cross(v1->vector, v2->vector)));
			return 1;
		}
	}
	wiLua::SError(L, "VectorCross(Vector v1,v2) not enough arguments!");
	return 0;
}
int Vector_BindLua::Multiply(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Vector_BindLua* v1 = Luna<Vector_BindLua>::lightcheck(L, 1);
		Vector_BindLua* v2 = Luna<Vector_BindLua>::lightcheck(L, 2);
		if (v1 && v2)
		{
			Luna<Vector_BindLua>::push(L, new Vector_BindLua(XMVectorMultiply(v1->vector, v2->vector)));
			return 1;
		}
	}
	wiLua::SError(L, "VectorMultiply(Vector v1,v2) not enough arguments!");
	return 0;
}
int Vector_BindLua::Add(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Vector_BindLua* v1 = Luna<Vector_BindLua>::lightcheck(L, 1);
		Vector_BindLua* v2 = Luna<Vector_BindLua>::lightcheck(L, 2);
		if (v1 && v2)
		{
			Luna<Vector_BindLua>::push(L, new Vector_BindLua(XMVectorAdd(v1->vector, v2->vector)));
			return 1;
		}
	}
	wiLua::SError(L, "VectorAdd(Vector v1,v2) not enough arguments!");
	return 0;
}
int Vector_BindLua::Subtract(lua_State* L)
{
	int argc = wiLua::SGetArgCount(L);
	if (argc > 1)
	{
		Vector_BindLua* v1 = Luna<Vector_BindLua>::lightcheck(L, 1);
		Vector_BindLua* v2 = Luna<Vector_BindLua>::lightcheck(L, 2);
		if (v1 && v2)
		{
			Luna<Vector_BindLua>::push(L, new Vector_BindLua(XMVectorSubtract(v1->vector, v2->vector)));
			return 1;
		}
	}
	wiLua::SError(L, "VectorSubtract(Vector v1,v2) not enough arguments!");
	return 0;
}

void Vector_BindLua::Bind()
{
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;
		Luna<Vector_BindLua>::Register(wiLua::GetGlobal()->GetLuaState());
		wiLua::GetGlobal()->RegisterFunc("VectorAdd", Add);
		wiLua::GetGlobal()->RegisterFunc("VectorSubtract", Subtract);
		wiLua::GetGlobal()->RegisterFunc("VectorMultiply", Multiply);
		wiLua::GetGlobal()->RegisterFunc("VectorDot", Dot);
		wiLua::GetGlobal()->RegisterFunc("VectorCross", Cross);
	}
}


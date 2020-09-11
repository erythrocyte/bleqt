#ifndef BLE_SRC_GRIDTYPE_H_
#define BLE_SRC_GRIDTYPE_H_

#include <iostream>
#include <map>

#include "mapInit.hpp"

namespace ble_src
{

	struct GridType
	{

	public:
		enum TypeEnum
		{
			kRegular,
			kRadial,
			kSpheric
		};

		static std::string get_description(TypeEnum enumVal)
		{
			switch (enumVal)
			{
			case TypeEnum::kRadial:
				return "Radial";
			case TypeEnum::kRegular:
				return "Regular";
			case TypeEnum::kSpheric:
				return "Spheric";
			default:
				return "Undefined";
			}
		}

		TypeEnum get_enum(std::string val)
		{
			if (val == "Radial")
				return TypeEnum::kRegular;
			else if (val == "Spheric")
				return TypeEnum::kSpheric;
			else
				return TypeEnum::kRegular;
		}
	};

	typedef Iterator<GridType::TypeEnum, GridType::TypeEnum::kRegular, GridType::TypeEnum::kSpheric> GridTypeEnumIterator;

} // namespace ble_src

#endif

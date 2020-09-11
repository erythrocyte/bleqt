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
			std::map<TypeEnum, std::string> descriptions = get_descriptions();
			return descriptions.find(enumVal)->second;
		}

		TypeEnum get_enum(std::string val)
		{
			std::map<TypeEnum, std::string> descriptions = get_descriptions();
			TypeEnum result = TypeEnum::kRegular;
			for (const auto &d : descriptions)
			{
				if (d.second == val)
				{
					return d.first;
				}

			}

			return result;
		}

	private:
		static std::map<TypeEnum, std::string> get_descriptions()
		{
			std::map<TypeEnum, std::string> result;

			result.insert(std::make_pair(TypeEnum::kRadial, "Radial"));
			result.insert(std::make_pair(TypeEnum::kRegular, "Regular"));
			result.insert(std::make_pair(TypeEnum::kSpheric, "Spheric"));

			return result;
		}
	};

	typedef Iterator<GridType::TypeEnum, GridType::TypeEnum::kRegular, GridType::TypeEnum::kSpheric> GridTypeEnumIterator;

} // namespace ble_src

#endif

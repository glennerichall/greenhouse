// include/etl_shim.h
#pragma once

// ETL (dans cette version) référence std::is_same même en mode ETL_NO_STL.
// On fournit une version minimale pour éviter de dépendre de <type_traits>.
namespace std
{
    template <typename, typename>
    struct is_same
    {
        static const bool value = false;
    };

    template <typename T>
    struct is_same<T, T>
    {
        static const bool value = true;
    };
}
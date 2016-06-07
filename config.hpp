#ifndef CONFIG_HPP
#define CONFIG_HPP

#define BUILD_DLL 1

#ifdef BUILD_DLL
# define EXPORT __declspec(dllexport)
#else
# define EXPORT __declspec(dllimport)
#endif
#endif
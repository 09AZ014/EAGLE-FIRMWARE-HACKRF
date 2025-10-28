# Copyright 2014 Jared Boone <jared@sharebrained.com>
#
# This file is part of PortaPack.
# This file was borrowed from HackRF.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Ensure we search the host PATH for programs (not the target sysroot)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Locate full paths to the cross-compilers so CMake doesn't rely on PATH
find_program(ARM_NONE_EABI_GCC NAMES arm-none-eabi-gcc)
find_program(ARM_NONE_EABI_GXX NAMES arm-none-eabi-g++)

# Fallback to common locations inside our Docker images
if(NOT ARM_NONE_EABI_GCC)
	if(EXISTS "/opt/build/armbin/bin/arm-none-eabi-gcc")
		set(ARM_NONE_EABI_GCC "/opt/build/armbin/bin/arm-none-eabi-gcc")
	else()
		set(ARM_NONE_EABI_GCC "/usr/bin/arm-none-eabi-gcc")
	endif()
endif()
if(NOT ARM_NONE_EABI_GXX)
	if(EXISTS "/opt/build/armbin/bin/arm-none-eabi-g++")
		set(ARM_NONE_EABI_GXX "/opt/build/armbin/bin/arm-none-eabi-g++")
	else()
		set(ARM_NONE_EABI_GXX "/usr/bin/arm-none-eabi-g++")
	endif()
endif()

if(CMAKE_VERSION VERSION_LESS 3.6)
	include(CMakeForceCompiler)

	CMAKE_FORCE_C_COMPILER(${ARM_NONE_EABI_GCC} GNU)
	CMAKE_FORCE_CXX_COMPILER(${ARM_NONE_EABI_GXX} GNU)
else()
	set(CMAKE_C_COMPILER ${ARM_NONE_EABI_GCC})
	set(CMAKE_CXX_COMPILER ${ARM_NONE_EABI_GXX})
	set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()

execute_process(
  COMMAND ${CMAKE_C_COMPILER} -print-file-name=libc.a
  OUTPUT_VARIABLE CMAKE_INSTALL_PREFIX
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
get_filename_component(CMAKE_INSTALL_PREFIX
  "${CMAKE_INSTALL_PREFIX}" PATH
)
get_filename_component(CMAKE_INSTALL_PREFIX
  "${CMAKE_INSTALL_PREFIX}/.." REALPATH
)
set(CMAKE_INSTALL_PREFIX  ${CMAKE_INSTALL_PREFIX} CACHE FILEPATH
    "Install path prefix, prepended onto install directories.")

message(STATUS "Cross-compiling with the gcc-arm-embedded toolchain")
message(STATUS "Toolchain prefix: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
#set(CMAKE_LD ${CMAKE_INSTALL_PREFIX}/bin/ld CACHE INTERNAL "ld tool")
set(CMAKE_OBJCOPY ${CMAKE_INSTALL_PREFIX}/bin/objcopy CACHE INTERNAL "objcopy tool")

set(CMAKE_FIND_ROOT_PATH ${CMAKE_INSTALL_PREFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

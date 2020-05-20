/*******************************************************************************
 * rad_data.cpp
 *
 * This module contains a lookup table of sampling directions for radiosity.
 *
 * This file was written by Jim McElhiney.
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/public/povray/3.x/source/backend/lighting/rad_data.cpp $
 * $Revision: #1 $
 * $Change: 6069 $
 * $DateTime: 2013/11/06 11:59:40 $
 * $Author: chrisc $
 *******************************************************************************/

/************************************************************************
*  Radiosity calculation routies.
*
*  Implemented by and (c) 1996 Jim McElhiney, mcelhiney@acm.org or 71201,1326
*  All standard POV distribution rights granted.  All other rights reserved.
*************************************************************************/

// frame.h must always be the first POV file included (pulls in platform config)
#include "backend/frame.h"
#include "backend/support/octree.h"

// this must be the last file included
#include "base/povdebug.h"

namespace pov
{

BYTE_XYZ rad_samples[1600] = {
	{ 250, 71, 127 },
	{ 116, 251, 109 },
	{ 146, 191, 45 },
	{ 110, 71, 249 },
	{ 196, 186, 182 },
	{ 178, 71, 16 },
	{ 80, 232, 150 },
	{ 9, 94, 127 },
	{ 147, 252, 125 },
	{ 205, 94, 38 },
	{ 217, 181, 117 },
	{ 241, 94, 94 },
	{ 113, 252, 142 },
	{ 231, 71, 194 },
	{ 43, 187, 145 },
	{ 170, 183, 206 },
	{ 172, 233, 154 },
	{ 111, 182, 215 },
	{ 78, 94, 235 },
	{ 78, 94, 20 },
	{ 163, 234, 91 },
	{ 110, 71, 6 },
	{ 10, 71, 162 },
	{ 41, 185, 111 },
	{ 208, 194, 149 },
	{ 57, 190, 176 },
	{ 96, 229, 81 },
	{ 138, 215, 195 },
	{ 59, 195, 82 },
	{ 241, 94, 161 },
	{ 47, 71, 220 },
	{ 106, 231, 177 },
	{ 178, 189, 58 },
	{ 47, 71, 35 },
	{ 178, 71, 239 },
	{ 131, 234, 77 },
	{ 201, 190, 85 },
	{ 144, 94, 245 },
	{ 144, 94, 10 },
	{ 80, 185, 201 },
	{ 183, 229, 120 },
	{ 28, 94, 192 },
	{ 10, 71, 93 },
	{ 77, 181, 53 },
	{ 28, 94, 63 },
	{ 140, 245, 161 },
	{ 111, 193, 46 },
	{ 78, 234, 114 },
	{ 231, 71, 61 },
	{ 219, 156, 171 },
	{ 205, 94, 217 },
	{ 155, 218, 67 },
	{ 35, 155, 87 },
	{ 229, 153, 139 },
	{ 155, 229, 177 },
	{ 90, 244, 134 },
	{ 47, 137, 198 },
	{ 24, 145, 143 },
	{ 150, 248, 146 },
	{ 111, 220, 65 },
	{ 89, 168, 39 },
	{ 98, 241, 158 },
	{ 187, 219, 101 },
	{ 104, 141, 24 },
	{ 222, 150, 86 },
	{ 117, 243, 90 },
	{ 78, 211, 76 },
	{ 60, 208, 158 },
	{ 129, 255, 131 },
	{ 179, 211, 78 },
	{ 65, 216, 100 },
	{ 197, 214, 133 },
	{ 186, 146, 214 },
	{ 121, 248, 157 },
	{ 104, 250, 122 },
	{ 65, 181, 192 },
	{ 145, 242, 91 },
	{ 175, 212, 181 },
	{ 128, 234, 178 },
	{ 208, 143, 196 },
	{ 138, 183, 216 },
	{ 137, 251, 108 },
	{ 119, 212, 198 },
	{ 54, 208, 123 },
	{ 34, 154, 168 },
	{ 191, 211, 161 },
	{ 159, 149, 226 },
	{ 129, 160, 28 },
	{ 204, 156, 61 },
	{ 124, 142, 233 },
	{ 67, 224, 135 },
	{ 23, 142, 111 },
	{ 52, 154, 59 },
	{ 168, 158, 36 },
	{ 81, 218, 175 },
	{ 67, 137, 216 },
	{ 92, 157, 222 },
	{ 92, 239, 100 },
	{ 168, 241, 132 },
	{ 247, 82, 145 },
	{ 97, 207, 195 },
	{ 251, 50, 109 },
	{ 152, 212, 194 },
	{ 60, 50, 22 },
	{ 241, 50, 76 },
	{ 17, 80, 178 },
	{ 191, 97, 28 },
	{ 215, 176, 99 },
	{ 161, 112, 18 },
	{ 17, 78, 77 },
	{ 236, 87, 177 },
	{ 218, 90, 50 },
	{ 183, 187, 194 },
	{ 106, 138, 232 },
	{ 127, 103, 11 },
	{ 172, 235, 107 },
	{ 234, 140, 122 },
	{ 194, 154, 50 },
	{ 155, 244, 103 },
	{ 40, 186, 129 },
	{ 97, 199, 53 },
	{ 141, 212, 58 },
	{ 162, 193, 52 },
	{ 44, 158, 73 },
	{ 123, 208, 54 },
	{ 60, 141, 45 },
	{ 73, 139, 35 },
	{ 42, 155, 182 },
	{ 156, 240, 161 },
	{ 154, 187, 210 },
	{ 25, 153, 127 },
	{ 49, 190, 96 },
	{ 217, 141, 70 },
	{ 214, 186, 134 },
	{ 230, 144, 105 },
	{ 193, 217, 115 },
	{ 170, 226, 168 },
	{ 164, 244, 119 },
	{ 160, 228, 81 },
	{ 142, 148, 230 },
	{ 181, 156, 42 },
	{ 174, 138, 224 },
	{ 205, 187, 167 },
	{ 144, 147, 25 },
	{ 219, 135, 185 },
	{ 89, 131, 25 },
	{ 23, 134, 158 },
	{ 124, 171, 222 },
	{ 195, 158, 201 },
	{ 129, 247, 95 },
	{ 128, 223, 66 },
	{ 142, 232, 178 },
	{ 70, 213, 88 },
	{ 123, 254, 120 },
	{ 154, 166, 35 },
	{ 98, 246, 144 },
	{ 96, 245, 111 },
	{ 24, 133, 95 },
	{ 183, 230, 133 },
	{ 91, 216, 185 },
	{ 128, 200, 207 },
	{ 114, 233, 77 },
	{ 64, 161, 203 },
	{ 186, 207, 173 },
	{ 77, 234, 132 },
	{ 179, 221, 91 },
	{ 131, 189, 42 },
	{ 103, 238, 90 },
	{ 72, 217, 165 },
	{ 84, 227, 89 },
	{ 169, 210, 68 },
	{ 78, 230, 102 },
	{ 109, 221, 189 },
	{ 194, 214, 147 },
	{ 55, 208, 141 },
	{ 162, 243, 143 },
	{ 118, 239, 171 },
	{ 109, 244, 159 },
	{ 205, 202, 121 },
	{ 142, 253, 137 },
	{ 91, 231, 167 },
	{ 87, 176, 210 },
	{ 148, 250, 113 },
	{ 73, 202, 184 },
	{ 180, 229, 146 },
	{ 78, 134, 224 },
	{ 125, 224, 188 },
	{ 108, 247, 103 },
	{ 131, 252, 147 },
	{ 203, 200, 102 },
	{ 103, 194, 206 },
	{ 51, 116, 211 },
	{ 144, 230, 75 },
	{ 88, 242, 121 },
	{ 224, 156, 155 },
	{ 4, 50, 110 },
	{ 114, 170, 33 },
	{ 90, 211, 66 },
	{ 47, 185, 162 },
	{ 133, 50, 252 },
	{ 165, 208, 191 },
	{ 3, 48, 140 },
	{ 86, 42, 246 },
	{ 160, 49, 248 },
	{ 66, 42, 237 },
	{ 33, 67, 49 },
	{ 67, 185, 64 },
	{ 156, 42, 5 },
	{ 36, 81, 207 },
	{ 200, 45, 230 },
	{ 86, 42, 9 },
	{ 202, 175, 72 },
	{ 66, 223, 122 },
	{ 54, 205, 108 },
	{ 187, 102, 228 },
	{ 212, 104, 207 },
	{ 99, 88, 244 },
	{ 46, 115, 48 },
	{ 12, 100, 149 },
	{ 166, 106, 237 },
	{ 136, 254, 118 },
	{ 189, 208, 86 },
	{ 123, 97, 245 },
	{ 228, 112, 74 },
	{ 102, 225, 73 },
	{ 98, 93, 12 },
	{ 180, 127, 30 },
	{ 59, 86, 226 },
	{ 115, 254, 128 },
	{ 168, 42, 9 },
	{ 40, 127, 60 },
	{ 30, 127, 179 },
	{ 208, 169, 179 },
	{ 153, 121, 237 },
	{ 230, 130, 167 },
	{ 91, 121, 234 },
	{ 191, 178, 62 },
	{ 33, 170, 118 },
	{ 14, 116, 117 },
	{ 205, 127, 49 },
	{ 192, 194, 75 },
	{ 54, 173, 185 },
	{ 32, 131, 74 },
	{ 38, 172, 157 },
	{ 67, 222, 111 },
	{ 220, 104, 198 },
	{ 31, 161, 105 },
	{ 61, 109, 34 },
	{ 246, 42, 171 },
	{ 188, 138, 39 },
	{ 105, 172, 36 },
	{ 165, 168, 216 },
	{ 103, 250, 133 },
	{ 223, 169, 128 },
	{ 127, 252, 108 },
	{ 169, 126, 25 },
	{ 56, 177, 71 },
	{ 14, 107, 104 },
	{ 130, 242, 168 },
	{ 63, 217, 147 },
	{ 234, 112, 85 },
	{ 140, 173, 35 },
	{ 243, 104, 118 },
	{ 214, 176, 159 },
	{ 79, 199, 64 },
	{ 135, 130, 18 },
	{ 143, 200, 205 },
	{ 47, 178, 84 },
	{ 37, 126, 192 },
	{ 153, 249, 136 },
	{ 212, 166, 80 },
	{ 149, 168, 221 },
	{ 24, 120, 84 },
	{ 240, 120, 132 },
	{ 120, 143, 22 },
	{ 240, 111, 106 },
	{ 209, 182, 91 },
	{ 85, 239, 142 },
	{ 123, 254, 138 },
	{ 47, 198, 134 },
	{ 106, 205, 55 },
	{ 208, 194, 110 },
	{ 198, 131, 212 },
	{ 90, 238, 153 },
	{ 64, 166, 54 },
	{ 79, 166, 44 },
	{ 16, 121, 136 },
	{ 55, 160, 195 },
	{ 140, 250, 148 },
	{ 183, 227, 109 },
	{ 104, 237, 168 },
	{ 147, 247, 103 },
	{ 10, 42, 173 },
	{ 82, 228, 162 },
	{ 115, 158, 227 },
	{ 172, 178, 48 },
	{ 94, 227, 175 },
	{ 46, 174, 172 },
	{ 204, 202, 140 },
	{ 148, 238, 169 },
	{ 227, 158, 116 },
	{ 39, 173, 98 },
	{ 181, 198, 68 },
	{ 112, 116, 15 },
	{ 223, 107, 62 },
	{ 228, 143, 95 },
	{ 228, 120, 179 },
	{ 159, 247, 128 },
	{ 182, 171, 205 },
	{ 83, 202, 191 },
	{ 174, 237, 126 },
	{ 74, 229, 142 },
	{ 67, 199, 75 },
	{ 74, 167, 208 },
	{ 103, 163, 223 },
	{ 108, 207, 199 },
	{ 68, 205, 174 },
	{ 193, 219, 125 },
	{ 172, 237, 141 },
	{ 201, 200, 157 },
	{ 98, 185, 44 },
	{ 144, 224, 186 },
	{ 118, 195, 209 },
	{ 196, 196, 171 },
	{ 136, 200, 49 },
	{ 160, 198, 201 },
	{ 212, 133, 59 },
	{ 51, 198, 152 },
	{ 196, 205, 95 },
	{ 71, 222, 155 },
	{ 171, 223, 84 },
	{ 165, 222, 178 },
	{ 98, 180, 213 },
	{ 162, 240, 153 },
	{ 221, 169, 106 },
	{ 58, 199, 166 },
	{ 120, 251, 149 },
	{ 107, 248, 149 },
	{ 189, 222, 140 },
	{ 46, 195, 119 },
	{ 130, 213, 198 },
	{ 100, 214, 64 },
	{ 134, 161, 226 },
	{ 184, 222, 154 },
	{ 137, 254, 127 },
	{ 234, 130, 155 },
	{ 88, 220, 76 },
	{ 115, 210, 56 },
	{ 140, 224, 68 },
	{ 237, 126, 144 },
	{ 58, 203, 93 },
	{ 59, 214, 131 },
	{ 137, 247, 98 },
	{ 91, 194, 201 },
	{ 80, 156, 217 },
	{ 87, 239, 110 },
	{ 74, 222, 94 },
	{ 173, 231, 97 },
	{ 100, 220, 186 },
	{ 83, 142, 32 },
	{ 173, 237, 116 },
	{ 152, 232, 80 },
	{ 31, 162, 149 },
	{ 191, 182, 190 },
	{ 77, 234, 123 },
	{ 120, 192, 44 },
	{ 159, 181, 43 },
	{ 148, 245, 156 },
	{ 156, 219, 186 },
	{ 131, 248, 157 },
	{ 124, 175, 35 },
	{ 154, 239, 92 },
	{ 123, 241, 86 },
	{ 202, 165, 190 },
	{ 94, 234, 90 },
	{ 156, 248, 116 },
	{ 120, 223, 66 },
	{ 159, 207, 60 },
	{ 173, 197, 194 },
	{ 207, 199, 129 },
	{ 101, 243, 100 },
	{ 163, 241, 106 },
	{ 197, 119, 39 },
	{ 122, 233, 76 },
	{ 156, 142, 26 },
	{ 141, 238, 83 },
	{ 131, 214, 58 },
	{ 110, 252, 116 },
	{ 117, 222, 189 },
	{ 117, 232, 179 },
	{ 108, 236, 83 },
	{ 164, 219, 74 },
	{ 85, 233, 98 },
	{ 57, 139, 208 },
	{ 179, 221, 164 },
	{ 33, 170, 137 },
	{ 119, 248, 99 },
	{ 218, 175, 145 },
	{ 96, 155, 31 },
	{ 213, 36, 221 },
	{ 133, 242, 87 },
	{ 250, 36, 159 },
	{ 19, 36, 192 },
	{ 212, 36, 34 },
	{ 18, 43, 66 },
	{ 222, 57, 209 },
	{ 10, 36, 82 },
	{ 247, 36, 87 },
	{ 38, 36, 217 },
	{ 253, 36, 136 },
	{ 152, 202, 54 },
	{ 250, 48, 100 },
	{ 69, 86, 23 },
	{ 31, 36, 209 },
	{ 135, 82, 7 },
	{ 181, 198, 187 },
	{ 188, 45, 238 },
	{ 149, 128, 19 },
	{ 136, 103, 244 },
	{ 101, 36, 4 },
	{ 57, 36, 233 },
	{ 43, 88, 43 },
	{ 18, 103, 166 },
	{ 119, 65, 4 },
	{ 101, 36, 251 },
	{ 196, 106, 221 },
	{ 179, 153, 216 },
	{ 5, 66, 119 },
	{ 237, 58, 68 },
	{ 69, 121, 223 },
	{ 185, 165, 49 },
	{ 187, 60, 19 },
	{ 5, 45, 101 },
	{ 4, 39, 154 },
	{ 30, 79, 200 },
	{ 237, 53, 187 },
	{ 70, 161, 47 },
	{ 163, 235, 162 },
	{ 111, 244, 94 },
	{ 71, 181, 198 },
	{ 200, 76, 30 },
	{ 115, 137, 234 },
	{ 134, 138, 235 },
	{ 226, 62, 53 },
	{ 59, 214, 116 },
	{ 188, 196, 182 },
	{ 138, 239, 171 },
	{ 212, 87, 43 },
	{ 17, 126, 126 },
	{ 235, 133, 113 },
	{ 242, 100, 152 },
	{ 84, 196, 59 },
	{ 15, 86, 86 },
	{ 59, 123, 216 },
	{ 65, 195, 181 },
	{ 234, 129, 100 },
	{ 115, 243, 163 },
	{ 228, 151, 147 },
	{ 55, 143, 51 },
	{ 133, 223, 189 },
	{ 32, 156, 96 },
	{ 153, 99, 13 },
	{ 35, 36, 42 },
	{ 86, 93, 16 },
	{ 176, 145, 35 },
	{ 162, 230, 171 },
	{ 78, 219, 84 },
	{ 221, 36, 43 },
	{ 36, 148, 78 },
	{ 24, 115, 174 },
	{ 174, 112, 232 },
	{ 203, 143, 201 },
	{ 28, 158, 135 },
	{ 105, 248, 109 },
	{ 48, 156, 66 },
	{ 135, 194, 210 },
	{ 210, 154, 187 },
	{ 97, 247, 129 },
	{ 209, 156, 68 },
	{ 151, 147, 229 },
	{ 39, 142, 69 },
	{ 106, 110, 240 },
	{ 23, 92, 184 },
	{ 53, 114, 41 },
	{ 49, 158, 189 },
	{ 24, 101, 72 },
	{ 231, 150, 130 },
	{ 84, 183, 50 },
	{ 166, 202, 60 },
	{ 175, 236, 137 },
	{ 20, 130, 150 },
	{ 238, 98, 169 },
	{ 222, 156, 163 },
	{ 177, 217, 172 },
	{ 44, 112, 206 },
	{ 56, 204, 100 },
	{ 115, 110, 242 },
	{ 22, 143, 120 },
	{ 246, 94, 136 },
	{ 51, 178, 78 },
	{ 183, 129, 222 },
	{ 149, 213, 61 },
	{ 163, 145, 29 },
	{ 97, 134, 23 },
	{ 196, 165, 58 },
	{ 200, 207, 110 },
	{ 38, 154, 175 },
	{ 91, 186, 48 },
	{ 124, 188, 213 },
	{ 158, 162, 221 },
	{ 213, 184, 151 },
	{ 98, 143, 229 },
	{ 220, 144, 78 },
	{ 82, 210, 183 },
	{ 84, 240, 128 },
	{ 42, 175, 91 },
	{ 66, 138, 39 },
	{ 216, 130, 192 },
	{ 151, 201, 202 },
	{ 146, 186, 213 },
	{ 190, 154, 208 },
	{ 76, 119, 27 },
	{ 73, 199, 69 },
	{ 48, 193, 104 },
	{ 74, 36, 242 },
	{ 72, 185, 59 },
	{ 216, 153, 179 },
	{ 131, 180, 218 },
	{ 123, 244, 164 },
	{ 219, 163, 93 },
	{ 110, 195, 208 },
	{ 168, 239, 148 },
	{ 188, 173, 199 },
	{ 202, 184, 175 },
	{ 83, 119, 231 },
	{ 128, 200, 49 },
	{ 77, 219, 169 },
	{ 127, 136, 20 },
	{ 16, 107, 97 },
	{ 185, 179, 57 },
	{ 46, 133, 55 },
	{ 120, 114, 14 },
	{ 53, 197, 160 },
	{ 170, 191, 54 },
	{ 162, 184, 209 },
	{ 31, 155, 159 },
	{ 122, 255, 128 },
	{ 152, 77, 247 },
	{ 45, 188, 154 },
	{ 54, 97, 220 },
	{ 59, 170, 62 },
	{ 112, 136, 21 },
	{ 72, 226, 106 },
	{ 93, 203, 59 },
	{ 105, 250, 141 },
	{ 167, 140, 227 },
	{ 138, 162, 29 },
	{ 143, 125, 238 },
	{ 181, 223, 96 },
	{ 35, 132, 185 },
	{ 135, 230, 182 },
	{ 23, 137, 103 },
	{ 162, 245, 135 },
	{ 26, 135, 166 },
	{ 226, 106, 188 },
	{ 212, 189, 142 },
	{ 10, 95, 141 },
	{ 33, 96, 56 },
	{ 89, 205, 193 },
	{ 50, 174, 179 },
	{ 160, 129, 232 },
	{ 160, 239, 98 },
	{ 128, 120, 240 },
	{ 159, 95, 241 },
	{ 148, 159, 30 },
	{ 195, 210, 103 },
	{ 148, 178, 39 },
	{ 174, 165, 42 },
	{ 71, 96, 231 },
	{ 104, 115, 16 },
	{ 93, 109, 17 },
	{ 153, 190, 47 },
	{ 137, 253, 142 },
	{ 211, 173, 170 },
	{ 212, 191, 123 },
	{ 141, 168, 222 },
	{ 33, 171, 127 },
	{ 222, 171, 137 },
	{ 114, 248, 153 },
	{ 178, 105, 23 },
	{ 53, 191, 88 },
	{ 96, 247, 122 },
	{ 60, 183, 185 },
	{ 83, 210, 70 },
	{ 197, 177, 67 },
	{ 155, 235, 168 },
	{ 95, 220, 72 },
	{ 182, 207, 179 },
	{ 143, 253, 120 },
	{ 118, 177, 219 },
	{ 130, 255, 124 },
	{ 111, 237, 172 },
	{ 104, 213, 193 },
	{ 108, 227, 72 },
	{ 132, 176, 36 },
	{ 205, 121, 209 },
	{ 136, 206, 202 },
	{ 41, 186, 137 },
	{ 148, 223, 69 },
	{ 112, 183, 40 },
	{ 188, 191, 69 },
	{ 204, 179, 79 },
	{ 139, 187, 42 },
	{ 72, 228, 117 },
	{ 115, 253, 121 },
	{ 191, 218, 108 },
	{ 234, 120, 92 },
	{ 130, 254, 139 },
	{ 175, 208, 72 },
	{ 188, 214, 93 },
	{ 63, 187, 70 },
	{ 60, 215, 138 },
	{ 155, 244, 152 },
	{ 70, 228, 128 },
	{ 195, 197, 82 },
	{ 167, 196, 199 },
	{ 124, 216, 60 },
	{ 161, 214, 67 },
	{ 123, 245, 93 },
	{ 36, 174, 111 },
	{ 214, 169, 87 },
	{ 96, 246, 138 },
	{ 148, 233, 175 },
	{ 88, 226, 83 },
	{ 209, 189, 100 },
	{ 200, 209, 127 },
	{ 179, 225, 158 },
	{ 184, 229, 126 },
	{ 217, 182, 127 },
	{ 61, 214, 107 },
	{ 19, 112, 90 },
	{ 75, 210, 177 },
	{ 92, 244, 116 },
	{ 108, 252, 128 },
	{ 164, 216, 184 },
	{ 52, 188, 169 },
	{ 153, 249, 122 },
	{ 171, 158, 218 },
	{ 66, 212, 162 },
	{ 33, 119, 66 },
	{ 197, 201, 164 },
	{ 126, 251, 151 },
	{ 174, 200, 63 },
	{ 51, 202, 114 },
	{ 114, 155, 27 },
	{ 102, 249, 115 },
	{ 246, 90, 111 },
	{ 190, 222, 132 },
	{ 40, 179, 104 },
	{ 116, 238, 83 },
	{ 188, 221, 148 },
	{ 175, 170, 210 },
	{ 227, 129, 82 },
	{ 171, 228, 91 },
	{ 196, 168, 194 },
	{ 48, 199, 127 },
	{ 64, 204, 170 },
	{ 241, 114, 125 },
	{ 207, 189, 158 },
	{ 203, 195, 94 },
	{ 90, 91, 240 },
	{ 81, 174, 208 },
	{ 130, 250, 102 },
	{ 60, 191, 77 },
	{ 201, 204, 149 },
	{ 235, 135, 137 },
	{ 135, 229, 71 },
	{ 162, 78, 11 },
	{ 85, 149, 222 },
	{ 65, 212, 93 },
	{ 90, 235, 160 },
	{ 219, 169, 154 },
	{ 82, 157, 38 },
	{ 85, 193, 199 },
	{ 34, 170, 143 },
	{ 57, 208, 149 },
	{ 199, 211, 119 },
	{ 88, 221, 177 },
	{ 171, 230, 161 },
	{ 224, 158, 100 },
	{ 181, 227, 104 },
	{ 166, 177, 44 },
	{ 137, 244, 91 },
	{ 171, 218, 77 },
	{ 71, 208, 81 },
	{ 186, 205, 79 },
	{ 41, 170, 166 },
	{ 150, 225, 183 },
	{ 172, 207, 187 },
	{ 129, 254, 115 },
	{ 104, 193, 48 },
	{ 197, 212, 140 },
	{ 137, 249, 154 },
	{ 155, 225, 74 },
	{ 212, 122, 201 },
	{ 156, 247, 143 },
	{ 187, 213, 166 },
	{ 28, 158, 114 },
	{ 202, 175, 183 },
	{ 149, 237, 86 },
	{ 212, 116, 52 },
	{ 85, 226, 169 },
	{ 91, 241, 146 },
	{ 66, 151, 210 },
	{ 94, 188, 207 },
	{ 97, 235, 167 },
	{ 61, 217, 124 },
	{ 105, 179, 215 },
	{ 114, 253, 135 },
	{ 99, 244, 151 },
	{ 38, 177, 150 },
	{ 161, 166, 37 },
	{ 151, 248, 108 },
	{ 167, 241, 112 },
	{ 234, 122, 161 },
	{ 89, 153, 33 },
	{ 223, 120, 69 },
	{ 164, 229, 85 },
	{ 67, 223, 141 },
	{ 80, 227, 94 },
	{ 111, 228, 182 },
	{ 112, 215, 195 },
	{ 143, 253, 131 },
	{ 167, 236, 100 },
	{ 202, 145, 54 },
	{ 120, 182, 39 },
	{ 102, 232, 81 },
	{ 104, 242, 161 },
	{ 159, 245, 111 },
	{ 123, 230, 182 },
	{ 91, 169, 215 },
	{ 209, 194, 116 },
	{ 117, 204, 203 },
	{ 176, 232, 149 },
	{ 114, 249, 102 },
	{ 222, 169, 113 },
	{ 81, 237, 137 },
	{ 142, 251, 111 },
	{ 224, 166, 121 },
	{ 96, 214, 189 },
	{ 146, 251, 142 },
	{ 135, 220, 63 },
	{ 83, 232, 156 },
	{ 99, 226, 179 },
	{ 117, 228, 71 },
	{ 134, 244, 163 },
	{ 21, 141, 134 },
	{ 105, 158, 30 },
	{ 82, 235, 107 },
	{ 124, 238, 173 },
	{ 62, 169, 197 },
	{ 42, 165, 81 },
	{ 198, 135, 46 },
	{ 135, 146, 23 },
	{ 104, 242, 95 },
	{ 100, 201, 201 },
	{ 43, 143, 191 },
	{ 116, 216, 61 },
	{ 178, 232, 114 },
	{ 89, 234, 93 },
	{ 241, 101, 100 },
	{ 135, 208, 54 },
	{ 49, 198, 143 },
	{ 29, 140, 88 },
	{ 107, 214, 61 },
	{ 170, 240, 122 },
	{ 151, 250, 131 },
	{ 83, 239, 118 },
	{ 128, 238, 82 },
	{ 65, 216, 153 },
	{ 214, 183, 108 },
	{ 148, 242, 163 },
	{ 182, 229, 140 },
	{ 116, 201, 50 },
	{ 90, 139, 228 },
	{ 187, 123, 33 },
	{ 164, 244, 126 },
	{ 72, 226, 149 },
	{ 177, 235, 131 },
	{ 124, 217, 194 },
	{ 126, 229, 72 },
	{ 41, 36, 35 },
	{ 151, 243, 97 },
	{ 176, 231, 102 },
	{ 188, 224, 117 },
	{ 156, 176, 215 },
	{ 94, 242, 106 },
	{ 137, 235, 79 },
	{ 145, 248, 151 },
	{ 143, 246, 98 },
	{ 253, 39, 122 },
	{ 49, 30, 28 },
	{ 173, 43, 245 },
	{ 208, 30, 225 },
	{ 2, 47, 127 },
	{ 140, 30, 253 },
	{ 125, 57, 252 },
	{ 218, 46, 215 },
	{ 94, 44, 249 },
	{ 52, 30, 229 },
	{ 193, 67, 232 },
	{ 27, 53, 54 },
	{ 95, 39, 6 },
	{ 226, 72, 200 },
	{ 14, 30, 72 },
	{ 52, 140, 203 },
	{ 72, 53, 16 },
	{ 250, 57, 151 },
	{ 75, 196, 190 },
	{ 53, 81, 32 },
	{ 194, 54, 22 },
	{ 129, 68, 5 },
	{ 227, 132, 173 },
	{ 242, 30, 182 },
	{ 254, 30, 115 },
	{ 167, 85, 14 },
	{ 6, 78, 134 },
	{ 27, 30, 204 },
	{ 22, 47, 60 },
	{ 15, 114, 110 },
	{ 117, 74, 249 },
	{ 16, 47, 184 },
	{ 141, 57, 4 },
	{ 30, 30, 46 },
	{ 181, 107, 230 },
	{ 5, 64, 145 },
	{ 11, 88, 156 },
	{ 40, 112, 54 },
	{ 162, 30, 6 },
	{ 136, 254, 135 },
	{ 145, 216, 193 },
	{ 173, 96, 18 },
	{ 240, 91, 88 },
	{ 217, 115, 57 },
	{ 80, 59, 13 },
	{ 166, 73, 244 },
	{ 202, 79, 223 },
	{ 80, 61, 242 },
	{ 17, 109, 160 },
	{ 211, 85, 214 },
	{ 184, 100, 25 },
	{ 40, 183, 117 },
	{ 125, 253, 144 },
	{ 129, 91, 247 },
	{ 64, 80, 231 },
	{ 47, 30, 225 },
	{ 16, 118, 144 },
	{ 5, 30, 95 },
	{ 9, 82, 106 },
	{ 227, 30, 206 },
	{ 198, 184, 74 },
	{ 217, 31, 38 },
	{ 120, 158, 28 },
	{ 188, 153, 46 },
	{ 64, 206, 87 },
	{ 85, 99, 237 },
	{ 225, 30, 47 },
	{ 47, 96, 214 },
	{ 206, 56, 31 },
	{ 184, 30, 14 },
	{ 232, 95, 182 },
	{ 191, 199, 176 },
	{ 173, 138, 31 },
	{ 5, 30, 161 },
	{ 183, 213, 84 },
	{ 172, 219, 176 },
	{ 103, 79, 9 },
	{ 57, 150, 203 },
	{ 57, 69, 27 },
	{ 102, 119, 237 },
	{ 232, 112, 174 },
	{ 150, 71, 7 },
	{ 63, 93, 28 },
	{ 139, 111, 13 },
	{ 63, 115, 221 },
	{ 209, 196, 136 },
	{ 67, 123, 34 },
	{ 36, 101, 201 },
	{ 7, 31, 88 },
	{ 121, 123, 239 },
	{ 139, 79, 248 },
	{ 73, 141, 219 },
	{ 159, 211, 192 },
	{ 229, 133, 88 },
	{ 27, 122, 78 },
	{ 236, 84, 74 },
	{ 178, 188, 198 },
	{ 183, 30, 241 },
	{ 124, 251, 104 },
	{ 95, 168, 37 },
	{ 132, 238, 173 },
	{ 190, 117, 222 },
	{ 177, 173, 48 },
	{ 192, 131, 216 },
	{ 142, 203, 51 },
	{ 242, 57, 176 },
	{ 30, 137, 173 },
	{ 183, 82, 235 },
	{ 127, 157, 228 },
	{ 236, 30, 193 },
	{ 9, 90, 113 },
	{ 39, 92, 48 },
	{ 141, 132, 19 },
	{ 27, 148, 154 },
	{ 147, 208, 199 },
	{ 248, 51, 93 },
	{ 41, 86, 211 },
	{ 217, 131, 64 },
	{ 78, 192, 195 },
	{ 241, 114, 139 },
	{ 115, 93, 9 },
	{ 202, 120, 43 },
	{ 203, 205, 134 },
	{ 193, 113, 34 },
	{ 181, 177, 53 },
	{ 122, 204, 204 },
	{ 68, 192, 187 },
	{ 208, 178, 84 },
	{ 37, 179, 123 },
	{ 10, 100, 121 },
	{ 60, 127, 40 },
	{ 155, 235, 86 },
	{ 81, 121, 25 },
	{ 31, 140, 82 },
	{ 193, 205, 89 },
	{ 144, 218, 64 },
	{ 73, 229, 136 },
	{ 91, 78, 12 },
	{ 172, 89, 238 },
	{ 232, 108, 79 },
	{ 100, 232, 173 },
	{ 222, 141, 177 },
	{ 84, 237, 146 },
	{ 95, 238, 96 },
	{ 133, 106, 12 },
	{ 226, 162, 133 },
	{ 89, 194, 54 },
	{ 103, 244, 155 },
	{ 119, 253, 142 },
	{ 70, 173, 53 },
	{ 218, 96, 204 },
	{ 106, 185, 42 },
	{ 82, 219, 80 },
	{ 224, 164, 142 },
	{ 60, 174, 191 },
	{ 225, 96, 194 },
	{ 54, 166, 65 },
	{ 216, 167, 165 },
	{ 210, 181, 164 },
	{ 246, 80, 105 },
	{ 50, 168, 72 },
	{ 151, 30, 252 },
	{ 109, 159, 225 },
	{ 188, 224, 126 },
	{ 199, 168, 63 },
	{ 120, 210, 56 },
	{ 107, 231, 78 },
	{ 238, 125, 119 },
	{ 93, 144, 28 },
	{ 40, 164, 170 },
	{ 28, 112, 185 },
	{ 231, 132, 95 },
	{ 152, 184, 42 },
	{ 42, 179, 159 },
	{ 250, 62, 141 },
	{ 102, 247, 146 },
	{ 167, 111, 20 },
	{ 100, 165, 34 },
	{ 84, 170, 43 },
	{ 129, 140, 234 },
	{ 109, 241, 165 },
	{ 22, 119, 168 },
	{ 156, 213, 64 },
	{ 156, 193, 206 },
	{ 117, 228, 184 },
	{ 200, 98, 35 },
	{ 129, 229, 184 },
	{ 50, 138, 53 },
	{ 172, 190, 200 },
	{ 159, 228, 175 },
	{ 249, 77, 117 },
	{ 137, 123, 239 },
	{ 52, 205, 131 },
	{ 79, 234, 143 },
	{ 56, 209, 112 },
	{ 220, 167, 99 },
	{ 134, 215, 196 },
	{ 202, 156, 196 },
	{ 109, 252, 120 },
	{ 73, 192, 64 },
	{ 162, 131, 24 },
	{ 178, 205, 184 },
	{ 45, 186, 101 },
	{ 127, 246, 160 },
	{ 164, 198, 56 },
	{ 19, 123, 100 },
	{ 72, 72, 237 },
	{ 157, 199, 54 },
	{ 97, 247, 133 },
	{ 72, 220, 160 },
	{ 48, 149, 194 },
	{ 207, 169, 75 },
	{ 76, 106, 231 },
	{ 63, 197, 176 },
	{ 86, 113, 21 },
	{ 184, 202, 73 },
	{ 56, 183, 181 },
	{ 234, 115, 168 },
	{ 35, 136, 72 },
	{ 196, 175, 190 },
	{ 95, 107, 239 },
	{ 124, 180, 218 },
	{ 104, 81, 246 },
	{ 156, 205, 198 },
	{ 40, 154, 76 },
	{ 129, 254, 119 },
	{ 213, 164, 175 },
	{ 178, 233, 118 },
	{ 148, 113, 240 },
	{ 125, 255, 134 },
	{ 100, 246, 108 },
	{ 134, 195, 45 },
	{ 28, 149, 100 },
	{ 60, 210, 103 },
	{ 36, 164, 162 },
	{ 146, 234, 81 },
	{ 44, 192, 131 },
	{ 62, 137, 212 },
	{ 97, 218, 69 },
	{ 150, 143, 24 },
	{ 65, 222, 129 },
	{ 149, 229, 75 },
	{ 17, 114, 154 },
	{ 129, 207, 202 },
	{ 223, 163, 149 },
	{ 67, 174, 198 },
	{ 56, 133, 45 },
	{ 126, 183, 39 },
	{ 66, 222, 117 },
	{ 115, 246, 158 },
	{ 86, 185, 204 },
	{ 47, 126, 203 },
	{ 195, 208, 158 },
	{ 55, 185, 77 },
	{ 242, 107, 146 },
	{ 146, 140, 233 },
	{ 70, 112, 29 },
	{ 168, 123, 232 },
	{ 222, 92, 55 },
	{ 20, 76, 71 },
	{ 110, 250, 108 },
	{ 177, 218, 83 },
	{ 69, 167, 204 },
	{ 53, 73, 224 },
	{ 207, 138, 56 },
	{ 12, 109, 132 },
	{ 99, 239, 93 },
	{ 192, 205, 168 },
	{ 130, 190, 212 },
	{ 131, 253, 143 },
	{ 164, 157, 221 },
	{ 86, 216, 181 },
	{ 178, 124, 227 },
	{ 33, 104, 196 },
	{ 243, 75, 166 },
	{ 207, 104, 43 },
	{ 108, 240, 90 },
	{ 159, 247, 121 },
	{ 84, 204, 65 },
	{ 41, 122, 199 },
	{ 185, 138, 218 },
	{ 165, 243, 139 },
	{ 75, 169, 48 },
	{ 88, 238, 105 },
	{ 141, 249, 104 },
	{ 246, 78, 156 },
	{ 136, 242, 167 },
	{ 166, 235, 158 },
	{ 160, 188, 48 },
	{ 58, 159, 56 },
	{ 89, 226, 172 },
	{ 145, 61, 250 },
	{ 17, 91, 172 },
	{ 24, 107, 179 },
	{ 133, 246, 94 },
	{ 183, 145, 38 },
	{ 207, 178, 173 },
	{ 29, 159, 141 },
	{ 188, 216, 156 },
	{ 206, 165, 184 },
	{ 250, 69, 134 },
	{ 114, 252, 114 },
	{ 101, 171, 218 },
	{ 13, 55, 79 },
	{ 79, 228, 98 },
	{ 157, 245, 148 },
	{ 227, 99, 65 },
	{ 74, 217, 88 },
	{ 206, 191, 97 },
	{ 22, 103, 78 },
	{ 143, 241, 166 },
	{ 160, 114, 237 },
	{ 92, 224, 78 },
	{ 65, 176, 59 },
	{ 90, 244, 129 },
	{ 186, 192, 188 },
	{ 68, 211, 168 },
	{ 42, 162, 176 },
	{ 199, 188, 79 },
	{ 108, 252, 135 },
	{ 84, 165, 214 },
	{ 27, 156, 119 },
	{ 241, 114, 113 },
	{ 71, 152, 42 },
	{ 118, 242, 167 },
	{ 26, 149, 148 },
	{ 118, 187, 214 },
	{ 127, 169, 32 },
	{ 94, 240, 155 },
	{ 65, 201, 81 },
	{ 212, 142, 191 },
	{ 241, 30, 71 },
	{ 229, 154, 122 },
	{ 164, 208, 64 },
	{ 159, 233, 87 },
	{ 146, 115, 15 },
	{ 68, 222, 148 },
	{ 158, 76, 245 },
	{ 204, 203, 115 },
	{ 71, 153, 213 },
	{ 73, 224, 100 },
	{ 79, 178, 205 },
	{ 108, 100, 12 },
	{ 136, 254, 123 },
	{ 125, 255, 125 },
	{ 54, 197, 95 },
	{ 125, 151, 25 },
	{ 119, 254, 133 },
	{ 50, 201, 121 },
	{ 121, 252, 110 },
	{ 231, 146, 111 },
	{ 186, 187, 63 },
	{ 236, 129, 107 },
	{ 141, 209, 199 },
	{ 236, 134, 128 },
	{ 61, 209, 97 },
	{ 36, 144, 180 },
	{ 31, 150, 92 },
	{ 226, 145, 162 },
	{ 119, 150, 230 },
	{ 177, 198, 191 },
	{ 12, 74, 168 },
	{ 81, 223, 168 },
	{ 169, 202, 193 },
	{ 148, 198, 50 },
	{ 92, 230, 86 },
	{ 206, 198, 145 },
	{ 200, 113, 216 },
	{ 142, 247, 155 },
	{ 110, 125, 237 },
	{ 60, 178, 66 },
	{ 150, 219, 189 },
	{ 176, 179, 204 },
	{ 181, 165, 46 },
	{ 8, 75, 151 },
	{ 239, 84, 81 },
	{ 64, 219, 141 },
	{ 78, 145, 220 },
	{ 166, 179, 210 },
	{ 34, 174, 132 },
	{ 182, 215, 169 },
	{ 73, 122, 226 },
	{ 133, 255, 129 },
	{ 214, 180, 103 },
	{ 86, 241, 136 },
	{ 174, 224, 167 },
	{ 190, 168, 55 },
	{ 148, 170, 35 },
	{ 156, 139, 231 },
	{ 195, 217, 129 },
	{ 77, 234, 119 },
	{ 77, 223, 163 },
	{ 105, 226, 182 },
	{ 198, 211, 114 },
	{ 120, 218, 62 },
	{ 122, 235, 177 },
	{ 102, 208, 58 },
	{ 168, 145, 31 },
	{ 160, 222, 181 },
	{ 56, 210, 135 },
	{ 46, 144, 60 },
	{ 146, 229, 181 },
	{ 70, 187, 192 },
	{ 103, 236, 85 },
	{ 76, 233, 128 },
	{ 124, 254, 114 },
	{ 214, 185, 112 },
	{ 97, 191, 49 },
	{ 129, 122, 16 },
	{ 120, 165, 224 },
	{ 208, 124, 205 },
	{ 168, 168, 41 },
	{ 59, 160, 199 },
	{ 152, 239, 164 },
	{ 96, 197, 202 },
	{ 78, 139, 33 },
	{ 178, 143, 220 },
	{ 64, 156, 49 },
	{ 180, 232, 129 },
	{ 161, 241, 102 },
	{ 181, 161, 210 },
	{ 94, 222, 181 },
	{ 100, 239, 164 },
	{ 79, 211, 180 },
	{ 173, 238, 132 },
	{ 79, 204, 187 },
	{ 136, 251, 147 },
	{ 213, 186, 146 },
	{ 238, 112, 156 },
	{ 245, 99, 130 },
	{ 167, 233, 95 },
	{ 88, 178, 45 },
	{ 136, 183, 39 },
	{ 118, 217, 193 },
	{ 142, 251, 144 },
	{ 200, 192, 169 },
	{ 168, 239, 107 },
	{ 130, 229, 72 },
	{ 97, 129, 233 },
	{ 139, 150, 25 },
	{ 217, 176, 150 },
	{ 227, 158, 127 },
	{ 17, 127, 121 },
	{ 224, 146, 169 },
	{ 113, 222, 188 },
	{ 131, 205, 52 },
	{ 19, 132, 131 },
	{ 137, 150, 230 },
	{ 159, 155, 31 },
	{ 29, 113, 70 },
	{ 232, 89, 69 },
	{ 55, 121, 213 },
	{ 110, 169, 34 },
	{ 79, 223, 89 },
	{ 74, 100, 23 },
	{ 139, 231, 75 },
	{ 76, 228, 153 },
	{ 48, 185, 90 },
	{ 120, 249, 153 },
	{ 121, 224, 188 },
	{ 152, 233, 172 },
	{ 206, 155, 191 },
	{ 157, 248, 133 },
	{ 200, 207, 144 },
	{ 100, 188, 209 },
	{ 102, 250, 127 },
	{ 116, 191, 44 },
	{ 151, 251, 125 },
	{ 190, 202, 81 },
	{ 166, 224, 80 },
	{ 197, 208, 153 },
	{ 73, 213, 172 },
	{ 35, 112, 61 },
	{ 64, 193, 74 },
	{ 199, 144, 50 },
	{ 146, 207, 56 },
	{ 97, 242, 102 },
	{ 76, 213, 81 },
	{ 155, 124, 20 },
	{ 175, 214, 77 },
	{ 120, 242, 88 },
	{ 198, 198, 89 },
	{ 45, 193, 139 },
	{ 51, 197, 101 },
	{ 40, 143, 186 },
	{ 135, 250, 103 },
	{ 175, 121, 26 },
	{ 143, 182, 39 },
	{ 86, 236, 151 },
	{ 102, 199, 52 },
	{ 74, 178, 202 },
	{ 217, 180, 140 },
	{ 84, 136, 226 },
	{ 86, 209, 187 },
	{ 51, 128, 207 },
	{ 212, 157, 73 },
	{ 56, 105, 36 },
	{ 51, 124, 47 },
	{ 158, 99, 14 },
	{ 89, 236, 99 },
	{ 97, 247, 117 },
	{ 104, 219, 188 },
	{ 92, 245, 124 },
	{ 175, 227, 160 },
	{ 132, 250, 152 },
	{ 114, 250, 147 },
	{ 153, 158, 224 },
	{ 27, 141, 161 },
	{ 92, 211, 190 },
	{ 117, 129, 18 },
	{ 103, 207, 198 },
	{ 62, 219, 134 },
	{ 122, 91, 8 },
	{ 198, 213, 124 },
	{ 144, 177, 218 },
	{ 23, 75, 190 },
	{ 81, 238, 131 },
	{ 162, 242, 148 },
	{ 195, 147, 207 },
	{ 121, 237, 81 },
	{ 40, 166, 86 },
	{ 214, 175, 93 },
	{ 159, 235, 165 },
	{ 192, 219, 120 },
	{ 143, 236, 173 },
	{ 136, 235, 176 },
	{ 119, 245, 161 },
	{ 106, 250, 114 },
	{ 218, 162, 88 },
	{ 212, 191, 130 },
	{ 85, 199, 195 },
	{ 82, 189, 55 },
	{ 218, 179, 122 },
	{ 52, 150, 198 },
	{ 78, 191, 59 },
	{ 215, 123, 197 },
	{ 184, 219, 161 },
	{ 184, 216, 90 },
	{ 182, 226, 150 },
	{ 145, 239, 86 },
	{ 232, 142, 143 },
	{ 156, 175, 39 },
	{ 98, 156, 224 },
	{ 191, 215, 103 },
	{ 20, 134, 140 },
	{ 38, 180, 142 },
	{ 109, 246, 98 },
	{ 91, 243, 140 },
	{ 27, 150, 107 },
	{ 203, 194, 162 },
	{ 169, 215, 182 },
	{ 134, 166, 31 },
	{ 112, 253, 124 },
	{ 192, 218, 143 },
	{ 100, 177, 40 },
	{ 88, 158, 219 },
	{ 128, 243, 89 },
	{ 119, 254, 124 },
	{ 196, 212, 108 },
	{ 232, 146, 134 },
	{ 96, 169, 218 },
	{ 221, 119, 190 },
	{ 215, 148, 184 },
	{ 54, 167, 190 },
	{ 162, 244, 114 },
	{ 106, 235, 172 },
	{ 129, 219, 62 },
	{ 59, 212, 144 },
	{ 55, 209, 118 },
	{ 141, 192, 210 },
	{ 134, 238, 83 },
	{ 219, 166, 159 },
	{ 232, 83, 188 },
	{ 223, 131, 74 },
	{ 30, 165, 123 },
	{ 32, 165, 111 },
	{ 120, 169, 32 },
	{ 87, 138, 28 },
	{ 214, 96, 47 },
	{ 34, 164, 154 },
	{ 153, 102, 242 },
	{ 150, 218, 65 },
	{ 205, 188, 89 },
	{ 150, 132, 234 },
	{ 83, 239, 124 },
	{ 109, 199, 50 },
	{ 205, 199, 107 },
	{ 52, 184, 174 },
	{ 173, 236, 111 },
	{ 22, 142, 125 },
	{ 117, 246, 95 },
	{ 78, 205, 70 },
	{ 62, 217, 112 },
	{ 87, 234, 158 },
	{ 52, 192, 164 },
	{ 40, 64, 40 },
	{ 107, 220, 67 },
	{ 46, 169, 78 },
	{ 176, 155, 39 },
	{ 67, 220, 105 },
	{ 193, 138, 43 },
	{ 224, 126, 183 },
	{ 174, 237, 121 },
	{ 175, 223, 88 },
	{ 43, 190, 123 },
	{ 165, 231, 166 },
	{ 170, 171, 212 },
	{ 135, 253, 112 },
	{ 185, 219, 96 },
	{ 94, 242, 149 },
	{ 229, 145, 152 },
	{ 192, 171, 196 },
	{ 160, 177, 213 },
	{ 152, 224, 71 },
	{ 182, 135, 34 },
	{ 225, 157, 105 },
	{ 99, 119, 19 },
	{ 56, 211, 127 },
	{ 112, 226, 71 },
	{ 106, 188, 211 },
	{ 53, 187, 83 },
	{ 209, 147, 63 },
	{ 148, 251, 136 },
	{ 160, 239, 157 },
	{ 153, 208, 58 },
	{ 121, 201, 49 },
	{ 115, 179, 37 },
	{ 153, 243, 157 },
	{ 76, 153, 39 },
	{ 46, 168, 178 },
	{ 95, 231, 170 },
	{ 42, 182, 153 },
	{ 77, 231, 108 },
	{ 116, 236, 175 },
	{ 124, 241, 169 },
	{ 111, 201, 204 },
	{ 223, 139, 81 },
	{ 153, 155, 30 },
	{ 176, 226, 94 },
	{ 19, 131, 114 },
	{ 192, 183, 66 },
	{ 101, 248, 139 },
	{ 107, 127, 19 },
	{ 47, 195, 110 },
	{ 237, 124, 150 },
	{ 167, 225, 173 },
	{ 206, 202, 125 },
	{ 146, 249, 108 },
	{ 110, 97, 244 },
	{ 63, 207, 164 },
	{ 113, 170, 221 },
	{ 140, 227, 184 },
	{ 229, 140, 158 },
	{ 177, 233, 143 },
	{ 224, 150, 91 },
	{ 92, 201, 197 },
	{ 104, 246, 104 },
	{ 213, 189, 119 },
	{ 73, 205, 75 },
	{ 150, 179, 216 },
	{ 200, 156, 57 },
	{ 192, 188, 185 },
	{ 48, 99, 41 },
	{ 156, 230, 80 },
	{ 32, 116, 189 },
	{ 111, 213, 59 },
	{ 148, 251, 119 },
	{ 47, 193, 148 },
	{ 198, 177, 186 },
	{ 109, 250, 144 },
	{ 37, 165, 92 },
	{ 80, 176, 49 },
	{ 77, 161, 212 },
	{ 183, 178, 200 },
	{ 226, 158, 110 },
	{ 151, 245, 102 },
	{ 192, 212, 97 },
	{ 79, 121, 228 },
	{ 111, 146, 231 },
	{ 143, 226, 71 },
	{ 112, 240, 87 },
	{ 193, 218, 137 },
	{ 69, 218, 97 },
	{ 49, 192, 157 },
	{ 137, 214, 59 },
	{ 181, 212, 174 },
	{ 168, 240, 143 },
	{ 209, 115, 48 },
	{ 139, 241, 87 },
	{ 178, 228, 153 },
	{ 28, 161, 130 },
	{ 144, 244, 160 },
	{ 216, 153, 76 },
	{ 169, 150, 222 },
	{ 207, 137, 200 },
	{ 197, 190, 177 },
	{ 180, 194, 63 },
	{ 77, 227, 158 },
	{ 44, 181, 95 },
	{ 111, 232, 177 },
	{ 24, 129, 90 },
	{ 98, 206, 59 },
	{ 123, 195, 209 },
	{ 125, 248, 99 },
	{ 237, 114, 97 },
	{ 100, 149, 28 },
	{ 125, 193, 44 },
	{ 55, 203, 155 },
	{ 73, 228, 112 },
	{ 167, 237, 153 },
	{ 14, 93, 91 },
	{ 151, 246, 151 },
	{ 133, 200, 206 },
	{ 51, 203, 138 },
	{ 130, 170, 223 },
	{ 119, 253, 116 },
	{ 98, 234, 86 },
	{ 154, 225, 182 },
	{ 127, 235, 78 },
	{ 136, 247, 159 },
	{ 60, 211, 152 },
	{ 128, 210, 55 },
	{ 142, 253, 125 },
	{ 149, 241, 91 },
	{ 95, 237, 162 },
	{ 155, 249, 127 },
	{ 133, 224, 67 },
	{ 169, 240, 137 },
	{ 191, 215, 152 },
	{ 193, 187, 71 },
	{ 163, 245, 131 },
	{ 59, 199, 88 },
	{ 158, 237, 93 },
	{ 114, 209, 199 },
	{ 89, 203, 61 },
	{ 43, 144, 65 },
	{ 143, 163, 31 },
	{ 146, 158, 226 },
	{ 104, 150, 228 },
	{ 86, 230, 164 },
	{ 175, 184, 53 },
	{ 103, 221, 69 },
	{ 48, 163, 184 },
	{ 84, 234, 102 },
	{ 200, 139, 206 },
	{ 72, 229, 123 },
	{ 31, 149, 164 },
	{ 229, 145, 100 },
	{ 122, 228, 70 },
	{ 62, 150, 207 },
	{ 119, 250, 105 },
	{ 170, 235, 102 },
	{ 184, 201, 183 },
	{ 108, 172, 219 },
	{ 199, 202, 98 },
	{ 124, 210, 200 },
	{ 42, 66, 217 },
	{ 167, 187, 50 },
	{ 58, 202, 161 },
	{ 151, 249, 141 },
	{ 141, 244, 94 },
	{ 187, 182, 194 },
	{ 232, 144, 117 },
	{ 175, 161, 214 },
	{ 38, 181, 134 },
	{ 35, 166, 101 },
	{ 177, 231, 108 },
	{ 89, 215, 71 },
	{ 92, 242, 110 },
	{ 88, 241, 116 },
	{ 169, 241, 127 },
	{ 204, 197, 153 },
	{ 183, 228, 115 },
	{ 109, 247, 153 },
	{ 154, 248, 112 },
	{ 186, 226, 136 },
	{ 70, 203, 179 },
	{ 147, 252, 131 },
	{ 167, 229, 88 },
	{ 139, 221, 190 },
	{ 46, 179, 167 },
	{ 159, 219, 71 },
	{ 129, 220, 192 },
	{ 148, 194, 208 },
	{ 185, 225, 144 },
	{ 109, 150, 26 },
	{ 170, 214, 72 },
	{ 83, 237, 112 },
	{ 136, 173, 221 },
	{ 98, 226, 77 },
	{ 168, 241, 117 },
	{ 217, 157, 82 },
	{ 95, 211, 64 },
	{ 161, 224, 76 },
	{ 66, 216, 157 },
	{ 111, 205, 54 },
	{ 186, 222, 106 },
	{ 188, 222, 112 },
	{ 179, 233, 124 },
	{ 221, 172, 117 }
};

}


#pragma once
#ifndef UTILS_GLDETECTION_H_
#define UTILS_GLDETECTION_H_

/*
   The Gl extension, must be one of: (E_GL_x)

     GL - 
     GLM - 
     GLEW - 
     GLFW - 


   Should be sorted most to least authoritative.
*/

#ifdef GL_VERSION_1_1
#define E_GL_GL

#endif // GL_VERSION_1_1

#ifdef GLM_SETUP_INCLUDED
#define E_GL_GLM
#endif // GLM_SETUP_INCLUDED

#ifdef __glew_h__
#define E_GL_GLEW
#endif // __glew_h__

#ifdef _glfw3_h_
#define E_GL_GLFW
#endif // _glfw3_h_



#endif // !UTILS_GLDETECTION_H_
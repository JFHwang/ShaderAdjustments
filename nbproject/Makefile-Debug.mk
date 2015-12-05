#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Ball.o \
	${OBJECTDIR}/BasicParticles.o \
	${OBJECTDIR}/BoundingSphere.o \
	${OBJECTDIR}/Brick.o \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/Color.o \
	${OBJECTDIR}/DrawData.o \
	${OBJECTDIR}/Drawable.o \
	${OBJECTDIR}/Frustum.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/Geode.o \
	${OBJECTDIR}/Globals.o \
	${OBJECTDIR}/Group.o \
	${OBJECTDIR}/KeyTracker.o \
	${OBJECTDIR}/Light.o \
	${OBJECTDIR}/Material.o \
	${OBJECTDIR}/MathTestBench.o \
	${OBJECTDIR}/Matrix4.o \
	${OBJECTDIR}/MatrixNode.o \
	${OBJECTDIR}/Mouse.o \
	${OBJECTDIR}/Movable.o \
	${OBJECTDIR}/Node.o \
	${OBJECTDIR}/OBJObject.o \
	${OBJECTDIR}/Paddle.o \
	${OBJECTDIR}/Particle.o \
	${OBJECTDIR}/ParticleSystem.o \
	${OBJECTDIR}/Point.o \
	${OBJECTDIR}/Shader.o \
	${OBJECTDIR}/SmartGeode.o \
	${OBJECTDIR}/Sphere.o \
	${OBJECTDIR}/UpdateData.o \
	${OBJECTDIR}/Vector3.o \
	${OBJECTDIR}/Vector4.o \
	${OBJECTDIR}/Wall.o \
	${OBJECTDIR}/Window.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C\glut\glut-3.7.6-bin -lfreeglut

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/temp.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/temp.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/temp ${OBJECTFILES} ${LDLIBSOPTIONS} -dynamic-lopengl32-LC:\FrGlut\lib\libfreeglut.a

${OBJECTDIR}/Ball.o: Ball.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ball.o Ball.cpp

${OBJECTDIR}/BasicParticles.o: BasicParticles.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BasicParticles.o BasicParticles.cpp

${OBJECTDIR}/BoundingSphere.o: BoundingSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BoundingSphere.o BoundingSphere.cpp

${OBJECTDIR}/Brick.o: Brick.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Brick.o Brick.cpp

${OBJECTDIR}/Camera.o: Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/Color.o: Color.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Color.o Color.cpp

${OBJECTDIR}/DrawData.o: DrawData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DrawData.o DrawData.cpp

${OBJECTDIR}/Drawable.o: Drawable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Drawable.o Drawable.cpp

${OBJECTDIR}/Frustum.o: Frustum.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Frustum.o Frustum.cpp

${OBJECTDIR}/Game.o: Game.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/Geode.o: Geode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Geode.o Geode.cpp

${OBJECTDIR}/Globals.o: Globals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Globals.o Globals.cpp

${OBJECTDIR}/Group.o: Group.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Group.o Group.cpp

${OBJECTDIR}/KeyTracker.o: KeyTracker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KeyTracker.o KeyTracker.cpp

${OBJECTDIR}/Light.o: Light.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Light.o Light.cpp

${OBJECTDIR}/Material.o: Material.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Material.o Material.cpp

${OBJECTDIR}/MathTestBench.o: MathTestBench.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MathTestBench.o MathTestBench.cpp

${OBJECTDIR}/Matrix4.o: Matrix4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Matrix4.o Matrix4.cpp

${OBJECTDIR}/MatrixNode.o: MatrixNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MatrixNode.o MatrixNode.cpp

${OBJECTDIR}/Mouse.o: Mouse.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mouse.o Mouse.cpp

${OBJECTDIR}/Movable.o: Movable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Movable.o Movable.cpp

${OBJECTDIR}/Node.o: Node.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Node.o Node.cpp

${OBJECTDIR}/OBJObject.o: OBJObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OBJObject.o OBJObject.cpp

${OBJECTDIR}/Paddle.o: Paddle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Paddle.o Paddle.cpp

${OBJECTDIR}/Particle.o: Particle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Particle.o Particle.cpp

${OBJECTDIR}/ParticleSystem.o: ParticleSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ParticleSystem.o ParticleSystem.cpp

${OBJECTDIR}/Point.o: Point.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Point.o Point.cpp

${OBJECTDIR}/Shader.o: Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Shader.o Shader.cpp

${OBJECTDIR}/SmartGeode.o: SmartGeode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SmartGeode.o SmartGeode.cpp

${OBJECTDIR}/Sphere.o: Sphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sphere.o Sphere.cpp

${OBJECTDIR}/UpdateData.o: UpdateData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UpdateData.o UpdateData.cpp

${OBJECTDIR}/Vector3.o: Vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vector3.o Vector3.cpp

${OBJECTDIR}/Vector4.o: Vector4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Vector4.o Vector4.cpp

${OBJECTDIR}/Wall.o: Wall.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Wall.o Wall.cpp

${OBJECTDIR}/Window.o: Window.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Window.o Window.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../../../FrGlut/freeglut/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/temp.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

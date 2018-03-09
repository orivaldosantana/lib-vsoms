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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/511e4115/BasicNeuralNetwork.o \
	${OBJECTDIR}/_ext/511e4115/Conexion.o \
	${OBJECTDIR}/_ext/511e4115/DataSet.o \
	${OBJECTDIR}/_ext/511e4115/Edge.o \
	${OBJECTDIR}/_ext/511e4115/Nodo.o \
	${OBJECTDIR}/_ext/511e4115/Sample.o \
	${OBJECTDIR}/_ext/511e4115/Weight.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvsoms.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvsoms.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvsoms.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvsoms.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvsoms.a

${OBJECTDIR}/_ext/511e4115/BasicNeuralNetwork.o: ../src/BasicNeuralNetwork.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/BasicNeuralNetwork.o ../src/BasicNeuralNetwork.cpp

${OBJECTDIR}/_ext/511e4115/Conexion.o: ../src/Conexion.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Conexion.o ../src/Conexion.cpp

${OBJECTDIR}/_ext/511e4115/DataSet.o: ../src/DataSet.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/DataSet.o ../src/DataSet.cpp

${OBJECTDIR}/_ext/511e4115/Edge.o: ../src/Edge.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Edge.o ../src/Edge.cpp

${OBJECTDIR}/_ext/511e4115/Nodo.o: ../src/Nodo.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Nodo.o ../src/Nodo.cpp

${OBJECTDIR}/_ext/511e4115/Sample.o: ../src/Sample.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Sample.o ../src/Sample.cpp

${OBJECTDIR}/_ext/511e4115/Weight.o: ../src/Weight.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Weight.o ../src/Weight.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

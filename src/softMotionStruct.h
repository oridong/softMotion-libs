/*
#
# Copyright (c) 2010 LAAS/CNRS
# All rights reserved.
#
# Permission to use, copy, modify, and distribute this software for any purpose
# with or without   fee is hereby granted, provided   that the above  copyright
# notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS  SOFTWARE INCLUDING ALL  IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR  BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER RESULTING  FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION,   ARISING OUT OF OR IN    CONNECTION WITH THE USE   OR
# PERFORMANCE OF THIS SOFTWARE.
#
#                                            Xavier BROQUERE on Fri Feb 26 2010
*/
/*--------------------------------------------------------------------
  Fichier              : softMotionStruct.h
  Fonction             : Structures definition for 3D Motion Trajectory Planning
  Date de creation     : Mai 2008
  Date de modification : Mai 2008
  Nb de lignes         :

  Auteur               : Xavier BROQUERE

----------------------------------------------------------------------*/

#ifndef SOFT_MOTION_STRUCT_H
#define SOFT_MOTION_STRUCT_H

#ifdef __cplusplus
#include <stdio.h>
#include <string.h>
#include <list>
#include <string>
#include <vector>

#endif

#include "softMotionConst.h"
typedef enum SM_STATUS {
  SM_OK    = 0,
  SM_ERROR = 1
} SM_STATUS;

typedef enum SM_SELECT {
	SM_ON  = 0,
	SM_OFF = 1
} SM_SELECT;  /* ON = 0, OFF = 1 */

typedef struct SM_TIMES {
	double Tjpa;
	double Taca;
	double Tjna;
	double Tvc;
	double Tjnb;
	double Tacb;
	double Tjpb;
} SM_TIMES ;

typedef struct SM_TIMES_DYN {
	int nseg;
	double* seg;
} SM_TIMES_DYN;

typedef struct SM_LIMITS {
  double maxJerk;
  double maxAcc;
  double maxVel;
} SM_LIMITS;

typedef struct SM_POSELIMITS {
  SM_LIMITS linear;
  SM_LIMITS angular;
} SM_POSELIMITS;

typedef struct SM_TIMES_GLOBAL {
  double T1;
  double T2;
  double T3;
  double T4;
  double T5;
  double T6;
  double T7;
} SM_TIMES_GLOBAL;

typedef struct SM_AXIS_TIMES {
  SM_TIMES PX;
  SM_TIMES PY;
  SM_TIMES PZ;
  SM_TIMES QN;
  SM_TIMES QI;
  SM_TIMES QJ;
  SM_TIMES QK;
} SM_AXIS_TIMES;

typedef struct SM_COND {
  double a;             /* Acceleration */
  double v;             /* Velocity     */
  double x;             /* Distance     */
} SM_COND;

typedef struct SM_JERKS {
  int sel;              /* Sel = 1   J1=J2=J3=J4    */
                        /* Sel = 4   J1, J2, J3, J4 */
  double J1;
  double J2;
  double J3;
  double J4;
  int withOutUseAlignment;
} SM_JERKS;

typedef struct SM_PARTICULAR_VELOCITY {
  double Vsmm;
  double Vsmp;
  double Vs0m;
  double Vs0p;
  double Vfmm;
  double Vfmp;
  double Vf0m;
  double Vf0p;
  double Vlim;
} SM_PARTICULAR_VELOCITY;

typedef struct SM_MOTION {
  SM_TIMES TNE; /* use this only for point to point motion in xarm */
  SM_TIMES Times[SM_NB_DIM]; /* en seconde */
  SM_TIMES TimesM[SM_NB_DIM];
  SM_TIMES Acc[SM_NB_DIM];
  SM_TIMES Vel[SM_NB_DIM];
  SM_TIMES Pos[SM_NB_DIM];
  SM_JERKS jerk[SM_NB_DIM];
  SM_COND  IC[SM_NB_DIM];
  SM_COND  FC[SM_NB_DIM];
  int      Dir[SM_NB_DIM];
  int      Dir_a[SM_NB_DIM];
  int      Dir_b[SM_NB_DIM];
  double   MotionDuration[SM_NB_DIM]; // motion duration of each axis
 	double      MotionDurationM[SM_NB_DIM];
	double TimeCumul[SM_NB_DIM][SM_NB_SEG];
  int      TimeCumulM[SM_NB_DIM][SM_NB_SEG];
	int      motionIsAdjusted[SM_NB_DIM];
} SM_MOTION;

typedef struct SM_MOTION_DYN {
	SM_TIMES* TNE;
	SM_TIMES* Times; /* en seconde */
	SM_TIMES* TimesM;
	SM_TIMES* Acc;
	SM_TIMES* Vel;
	SM_TIMES* Pos;
	SM_JERKS* jerk;
	SM_COND*  IC;
	SM_COND*  FC;
	double*  Jerk;
	int*     Dir;
	double*   MotionDuration; // motion duration of each axis
	double*   MotionDurationM;
	int*     TimeCumulM;
	int*      motionIsAdjusted;
} SM_MOTION_DYN;

typedef struct SM_MOTION_MONO {
	SM_TIMES Times; /* en seconde */
	SM_TIMES TimesM;
	SM_TIMES Acc;
	SM_TIMES Vel;
	SM_TIMES Pos;
	SM_JERKS jerk;
	SM_COND  IC;
	SM_COND  FC;
	double   Jerk;
	int      Dir;
	int      Dir_a;
	int      Dir_b;
	double   MotionDuration;
	double   MotionDurationM;
	double   TimeCumul[SM_NB_SEG];
	int      TimeCumulM[SM_NB_SEG];
	int      motionIsAdjusted;
} SM_MOTION_MONO;

typedef struct SM_TRANSITION_MOTION {
  SM_TIMES Times[SM_NB_DIM]; /* en seconde */
  SM_TIMES TimesM[SM_NB_DIM];
  SM_TIMES Acc_a[SM_NB_DIM];
  SM_TIMES Vel_a[SM_NB_DIM];
  SM_TIMES Pos_a[SM_NB_DIM];
  SM_JERKS jerk[SM_NB_DIM];
  SM_TIMES Acc_b[SM_NB_DIM];
  SM_TIMES Vel_b[SM_NB_DIM];
  SM_TIMES Pos_b[SM_NB_DIM];
  SM_TIMES Acc[SM_NB_DIM];
  SM_TIMES Vel[SM_NB_DIM];
  SM_TIMES Pos[SM_NB_DIM];
  int      Dir[SM_NB_DIM];
  SM_COND  IC[SM_NB_DIM];
  SM_COND  FC[SM_NB_DIM];
  int      Dir_a[SM_NB_DIM];
  int      Dir_b[SM_NB_DIM];
  int      MotionDuration[SM_NB_DIM];
  int      optimalTime[SM_NB_DIM]; /* en ticks */
  int      timeToStop;
} SM_TRANSITION_MOTION;

typedef struct SM_TIMES_ADJUSTED_MOTION {
  double Tvc0;
  double Tjpa;
  double Taca;
  double Tjna;
  double Tvc1;
  double Tjnb;
  double Tacb;
  double Tjpb;
  double Tvc2;
  double Tjpc;
  double Tacc;
  double Tjnc;
} SM_TIMES_ADJUSTED_MOTION;

typedef struct SM_SEGMENT {
	int type; /* 1 to 7 */
	double time;
	int timeM;
	double J;
	double A0;
	double V0;
	double X0;
	int dir;
} SM_SEGMENT;

typedef enum SM_INTERP_TYPE {
	SM_PASS_PTP  = 0,
	SM_PASS_BY   = 1,
	SM_PASS_NEAR = 2
} SM_INTERP_TYPE;

typedef struct SM_TIMES_STOP {
	double T1;
	double T2;
	double T3;
	double T4;
	double T5;
	double T6;
	double T7;
	double T8;
	double T9;
	double T10;
} SM_TIMES_STOP;

/*--------------------------- Trajectory defenition ---------------------*/
typedef struct SM_LINE_ARC{
	double invR0; // inverse of starting radius
	double invRf; // inverse of ending radius
	double Ls;    // length of line or arc
} SM_LINE_ARC;

typedef struct SM_CURVE_DATA{
	double t;       // time value of the given data
	double u;       // curvature abcissa
	double du;      // tangential velocity
	double ddu;     // tangential acceleration
	double Pos[3];  // cartesian coordinate
	double Vel[3];  // projected velocity in cartesian coordinate 
	double Acc[3];  // projected acceleration in cartesian coordinate 
         double Jerk[3];
	double AccNorm; // acceleration norm 
}SM_CURVE_DATA;

typedef struct SM_ROT{
	double thetaX; // angle of rotation /x
	double thetaY; // angle of rotation /y
	double thetaZ; // angle of rotation /z
	double R[3][3]; //rotation matrix
}SM_ROT;

typedef struct SM_COND_DIM{
	SM_COND Axis[3]; // Initial or final condition in 3 axis
} SM_COND_DIM;

typedef struct SM_OUTPUT{
	double Jerk[3]; // output jerk
	double Time[3]; // output time
	SM_COND IC[3]; // output initial condition (at the beginning of the segmnent, before applying Jerk)
}SM_OUTPUT;


#ifdef __cplusplus
typedef struct Point2D
{
  float x, y;
} Point2D;

typedef enum SubPathType
  {
    LINE,
    BEZIER3,
  } SubPathType;


typedef struct SubPath
{
  SubPathType type;
  Point2D start, end;
  Point2D bezier3[2]; // control point at start and end
} SubPath;

typedef struct Path
{
  Point2D origin;
  int nbSubPath;
  double length;
  std::list<SubPath> subpath;
} Path;


typedef struct kinPoint 
{
  SM_COND kc[3];
  double t;
} kinPoint;

typedef struct SubTraj
{
  std::vector<SM_CURVE_DATA> traj;
  std::vector<SM_OUTPUT> motion_par_seg;
  std::vector<SM_COND_DIM> IC_par_seg;
  std::vector<SM_COND_DIM> FC_par_seg;
  double err;
} SubTraj;


#endif


#endif

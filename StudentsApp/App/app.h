/*
 * app.h
 *
 *  Created on: 22 avr. 2022
 *      Author: Garnier
 */


typedef struct s_app t_app;

t_app*AppNew(void);
t_app*AppDel(t_app*pApp);
int AppRun(t_app*pApp);




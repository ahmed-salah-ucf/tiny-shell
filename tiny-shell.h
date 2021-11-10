#ifndef TINY_SHELL_H
#define TINY_SHELL_H

#include <stdlib.h>
#include <ctype.h>
#include "job.h"
#include "sig-handlers.h"
#include "wrappers.h"


/* Function prototypes */

/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
*/
void eval(char *cmdline);


/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.  
 */
int parseline(const char *cmdline, char **argv); 

/* 
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid);



/* 
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.  
 */
int builtin_cmd(char **argv);


/* 
 * do_bgfg - Execute the builtin bg and fg commands
 */
void do_bgfg(char **argv);


/*
 * usage - print a help message
 */
void usage(void);



/* 
 * isvalid - check if the bg and fg commands' argument is valid
 */
int isvalid(char *id);

#endif
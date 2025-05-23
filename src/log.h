/*! \file    log.h
 * \author   Jay Ridgeway <jayridge@gmail.com>
 * \copyright GNU General Public License v3
 * \brief    Buffered logging (headers)
 * \details   Implementation of a simple buffered logger designed to remove
 * I/O wait from threads that may be sensitive to such delays. Each time
 * there's stuff to be written (to stdout, log files, or external loggers),
 * it's added to an async queue, which is consumed from a dedicated thread
 * that then actually takes care of I/O.
 *
 * \ingroup core
 * \ref core
 */

#ifndef JANUS_LOG_H
#define JANUS_LOG_H

#include <stdio.h>
#include <glib.h>

/*! \brief Buffered vprintf
* @param[in] format Format string as defined by glib, followed by the
* optional parameters to insert into formatted string (printf style)
* \note This output is buffered and may not appear immediately on stdout. */
void janus_vprintf(const char *format, ...) G_GNUC_PRINTF(1, 2);

/*! \brief Log initialization
* \note This should be called before attempting to use the logger. A buffer
* pool and processing thread are created.
* @param daemon Whether the Janus is running as a daemon or not
* @param console Whether the output should be printed on stdout or not
* @param logfile Log file to save the output to, if any
* @param loggers Hash table of external loggers registered in the core, if any
* @returns 0 in case of success, a negative integer otherwise */
int janus_log_init(gboolean daemon, gboolean console, const char *logfile, GHashTable *loggers);
/*! \brief Reopen log file (log rotation) */
void janus_log_reload(void);
/*! \brief Log destruction */
void janus_log_destroy(void);

/*! \brief Method to check whether stdout logging is enabled
 * @returns TRUE if stdout logging is enabled, FALSE otherwise */
gboolean janus_log_is_stdout_enabled(void);
/*! \brief Method to check whether file-based logging is enabled
 * @returns TRUE if file-based logging is enabled, FALSE otherwise */
gboolean janus_log_is_logfile_enabled(void);
/*! \brief Method to get the path to the log file
 * @returns The full path to the log file, or NULL otherwise */
char *janus_log_get_logfile_path(void);

#endif

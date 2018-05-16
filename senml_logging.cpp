/*  _  __  ____    _   _ 
 * | |/ / |  _ \  | \ | |
 * | ' /  | |_) | |  \| |
 * | . \  |  __/  | |\  |
 * |_|\_\ |_|     |_| \_|
 * 
 * (c) 2018 KPN
 * License: GNU General Public License v3.0.
 * Author: Jan Bogaerts
 * 
 * logging
 */

#include <senml_logging.h>

Stream* _senml_logger = NULL;

void senMLSetLogger(Stream* logger){
    _senml_logger = logger;
};







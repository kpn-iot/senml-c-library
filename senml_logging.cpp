#include <senml_logging.h>

Stream* _senml_logger = NULL;

void senMLSetLogger(Stream* logger){
    _senml_logger = logger;
};
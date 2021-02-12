aux_source_directory(./socket api)
aux_source_directory(./log api)
aux_source_directory(. api)

add_library( APIS ${api})

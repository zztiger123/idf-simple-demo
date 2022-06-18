idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES "ca.pem"
                                   "server.pem"
                                   "server.key")

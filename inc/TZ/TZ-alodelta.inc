            drop_command                        =  *drop_cluster
+                                               |  *drop_databaselink
+                                               |  *drop_index
+                                               |  *drop_profile
+                                               |  *drop_role
+                                               |  *drop_rollback
+                                               |  *drop_snapshot
+                                               |  *drop_snapshotlog
+                                               |  *drop_sequence
+                                               |  *drop_synonym
+                                               |  *drop_table
+                                               |  *drop_tablespace
+                                               |  *drop_trigger
+                                               |  *drop_user
+                                               |  *drop_view
            drop_cluster                        =  DROP CLUSTER *cluster !(INCLUDING TABLES) !(CASCADE CONSTRAINTS)
            drop_databaselink                   =  DROP !PUBLIC DATABASE LINK *databaselink_name
            drop_function                       =  DROP *function
            drop_index                          =  DROP INDEX *index
            drop_package                        =  DROP *package
            drop_procedure                      =  DROP *procedure
            drop_profile                        =  DROP PROFILE *profile_name !CASCADE
            drop_role                           =  DROP ROLE *role_name
            drop_rollback                       =  DROP ROLLBACK SEGMENT *rollback_name
            drop_sequence                       =  DROP SEQUENCE *sequence
            drop_snapshot                       =  DROP SNAPSHOT *snapshot
            drop_snapshotlog                    =  DROP SNAPSHOT LOG ON *table
            drop_synonym                        =  DROP !PUBLIC SYNONYM *synonym
            drop_table                          =  DROP TABLE *table !(CASCADE CONSTRAINTS)
            drop_tablespace                     =  DROP
+                                                  TABLESPACE
+                                                  *tablespace_name
+                                                  !(INCLUDING CONTENTS)
+                                                  !(CASCADE CONSTRAINTS)
            drop_trigger                        =  DROP TRIGGER *trigger
            drop_user                           =  DROP USER *user_name !CASCADE
            drop_view                           =  DROP VIEW *view
            cluster_name                        =  *identifier
            databaselink_name                   =  *identifier
            function_name                       =  *identifier
            index_name                          =  *identifier
            profile_name                        =  *identifier
            procedure_name                      =  *identifier
            package_name                        =  *identifier
            role_name                           =  *identifier
            rollback_name                       =  *identifier
            sequence_name                       =  *identifier
            snapshot_name                       =  *identifier
            synonym_name                        =  *identifier
            table_name                          =  *identifier
            tablespace_name                     =  *identifier
            trigger_name                        =  *identifier
            user_name                           =  *identifier
            view_name                           =  *identifier
            cluster                             =  *cluster_name | *schema_name $'.' *cluster_name
            function                            =  *function_name | *schema_name $'.' *function_name
            index                               =  *index_name | *schema_name $'.' *index_name
            package                             =  *package_name | *schema_name $'.' *package_name
            procedure                           =  *procedure_name | *schema_name $'.' *procedure_name
            sequence                            =  *sequence_name | *schema_name $'.' *sequence_name
            snapshot                            =  *snapshot_name | *schema_name $'.' *snapshot_name
            synonym                             =  *synonym_name | *schema_name $'.' *synonym_name
            table                               =  *table_name | *schema_name $'.' *table_name
            trigger                             =  *trigger_name | *schema_name $'.' *trigger_name
            view                                =  *view_name | *schema_name $'.' *view_name
            grant_command                       =  *grant_object_priv | *grant_system_priv | *grant_role_priv
            grant_object_priv                   =  GRANT
+                                                  (*object_privilege !%($',' *object_privilege) | ALL !PRIVILEGE)
+                                                  !($'(' *grant_column_list $')')
+                                                  ON
+                                                  *object
+                                                  TO
+                                                  *distribution_list
+                                                  !(WITH GRANT OPTION)
            object_privilege                    =  ALTER
+                                               |  DELETE
+                                               |  EXECUTE
+                                               |  INDEX
+                                               |  INSERT
+                                               |  REFERENCES
+                                               |  SELECT
+                                               |  UPDATE
            grant_column                        =  *identifier
            grant_column_list                   =  *grant_column | *grant_column_list $',' *grant_column
            object_name                         =  *identifier
            object                              =  *object_name | *schema_name $'.' *object_name
            grant_role_priv                     =  GRANT *role_name TO *distribution_list
            grant_system_priv                   =  GRANT
+                                                  *system_privilege
+                                                  !%($',' *system_privilege)
+                                                  TO
+                                                  *distribution_list
+                                                  !(WITH ADMIN OPTION)
            distribution                        =  *user_name | *role_name | PUBLIC
            distribution_list                   =  *distribution !%($',' *distribution)
            system_privilege                    =  ALTER ANY CLUSTER
+                                               |  ALTER ANY INDEX
+                                               |  ALTER ANY PROCEDURE
+                                               |  ALTER ANY ROLE
+                                               |  ALTER ANY SEQUENCE
+                                               |  ALTER ANY SNAPSHOT
+                                               |  ALTER ANY TABLE
+                                               |  ALTER ANY TRIGGER
+                                               |  ALTER DATABASE
+                                               |  ALTER PROFILE
+                                               |  ALTER RESOURCE COST
+                                               |  ALTER ROLLBACK SEGMENT
+                                               |  ALTER SYSTEM
+                                               |  ALTER TABLESPACE
+                                               |  ALTER USER
+                                               |  ANALYZE ANY
+                                               |  AUDIT ANY
+                                               |  AUDIT SYSTEM
+                                               |  BACKUP ANY TABLE
+                                               |  BECOME USER
+                                               |  COMMENT ANY TABLE
+                                               |  CREATE ANY CLUSTER
+                                               |  CREATE ANY INDEX
+                                               |  CREATE ANY PROCEDURE
+                                               |  CREATE ANY SEQUENCE
+                                               |  CREATE ANY SNAPSHOT
+                                               |  CREATE ANY SYNONYM
+                                               |  CREATE ANY TABLE
+                                               |  CREATE ANY TRIGGER
+                                               |  CREATE ANY VIEW
+                                               |  CREATE PROFILE
+                                               |  CREATE PUBLIC DATABASE LINK
+                                               |  CREATE PUBLIC SYNONYM
+                                               |  CREATE ROLE
+                                               |  CREATE ROLLBACK SEGMENT
+                                               |  CREATE USER
+                                               |  DELETE ANY TABLE
+                                               |  DROP ANY CLUSTER
+                                               |  DROP ANY INDEX
+                                               |  DROP ANY PROCEDURE
+                                               |  DROP ANY ROLE
+                                               |  DROP ANY SEQUENCE
+                                               |  DROP ANY SNAPSHOT
+                                               |  DROP ANY SYNONYM
+                                               |  DROP ANY TABLE
+                                               |  DROP ANY TRIGGER
+                                               |  DROP ANY VIEW
+                                               |  DROP PROFILE
+                                               |  DROP PUBLIC DATABASE LINK
+                                               |  DROP PUBLIC SYNONYM
+                                               |  DROP ROLLBACK SEGMENT
+                                               |  DROP TABLESPACE
+                                               |  DROP USER
+                                               |  EXECUTE ANY PROCEDURE
+                                               |  FORCE ANY TRANSACTION
+                                               |  FORCE TRANSACTION
+                                               |  GRANT ANY PRIVILEGE
+                                               |  GRANT ANY ROLE
+                                               |  INSERT ANY TABLE
+                                               |  LOCK ANY TABLE
+                                               |  MANAGE TABLESPACE
+                                               |  RESTRICTED SESSION
+                                               |  SELECT ANY SEQUENCE
+                                               |  SELECT ANY TABLE
+                                               |  UNLIMITED TABLESPACE
+                                               |  UPDATE ANY TABLE

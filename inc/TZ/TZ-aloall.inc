            alias                               =  *identifier
            allocate_spec                       =  size *n !(k | m) | datafile $"'" *file_name $"'" | instance *n
            alter_cluster                       =  alter
+                                                  cluster
+                                                  !(*schema_name $'.')
+                                                  *cluster_name
+                                                  *alter_cluster_spec
+                                                  !%*alter_cluster_spec
            alter_cluster_spec                  =  pctused *n
+                                               |  pctfree *n
+                                               |  size *n !(k | m)
+                                               |  initrans *n
+                                               |  maxtrans *n
+                                               |  storage $'(' *storage_spec !%*storage_spec $')'
+                                               |  allocate extent !%*allocate_spec
            alter_command                       =  *alter_cluster
+                                               |  *alter_database
+                                               |  *alter_index
+                                               |  *alter_profile
+                                               |  *alter_cost
+                                               |  *alter_role
+                                               |  *alter_rollback
+                                               |  *alter_sequence
+                                               |  *alter_session
+                                               |  *alter_snapshot
+                                               |  *alter_snapshot_log
+                                               |  *alter_system
+                                               |  *alter_table
+                                               |  *alter_tablespace
+                                               |  *alter_trigger
+                                               |  *alter_user
+                                               |  *alter_view
            alter_cost                          =  alter resource cost *resource_cost_name *n
            alter_database                      =  alter
+                                                  database
+                                                  !*database_name
+                                                  (  mount !(parallel | exclusive)
+                                                  |  convert
+                                                  |  open !(resetlogs | noresetlogs)
+                                                  |  archive | noarchive
+                                                  |  recover *recover_clause
+                                                  |  add logfile *logfile_clause
+                                                  |  add logfile member *logmember_clause !%($',' *logmember_clause)
+                                                  |  drop logfile *group_file_list
+                                                  |  rename file *file_list to *file_list
+                                                  |  backup controlfile to *file_reuse
+                                                  |  create datafile *file_list !(as *file_spec_list)
+                                                  |  datafile $"'" *file_name $"'" !(online | offline !drop)
+                                                  |  enable !public thread *n
+                                                  |  disable thread *n
+                                                  |  rename global_name to *database_name !%($'.' *domain_name)
+                                                  )
            alter_index                         =  alter
+                                                  index
+                                                  !(*schema_name $'.')
+                                                  *index_name
+                                                  *alter_index_spec
+                                                  !%*alter_index_spec
            alter_index_spec                    =  initrans *n
+                                               |  maxtrans *n
+                                               |  storage $'(' *storage_spec !%*storage_spec $')'
            alter_profile                       =  alter profile *profile_name limit *profile_spec !%*profile_spec
            alter_role                          =  alter
+                                                  role
+                                                  *role_name
+                                                  (not identified | identified (by *password | externally))
            alter_rollback                      =  alter
+                                                  rollback
+                                                  segment
+                                                  *rollback_name
+                                                  (online | offline | storage $'(' *storage_spec !%*storage_spec $')')
            alter_sequence                      =  alter
+                                                  sequence
+                                                  !(*schema_name $'.')
+                                                  *sequence_name
+                                                  *alter_sequence_spec
+                                                  !%*alter_sequence_spec
            alter_sequence_spec                 =  increment by *n
+                                               |  maxvalue *n
+                                               |  nomaxvalue
+                                               |  minvalue *n
+                                               |  nominvalue
+                                               |  cycle | nocycle
+                                               |  cache *n
+                                               |  nocache
+                                               |  order | noorder
            alter_session                       =  alter
+                                                  session
+                                                  (  set *set_session_spec !%*set_session_spec
+                                                  |  close database link *link_name
+                                                  |  advise (commit | rollback | nothing)
+                                                  |  (enable | disable) commit in procedure
+                                                  )
            alter_snapshot                      =  alter
+                                                  snapshot
+                                                  !(*schema_name $'.')
+                                                  *snapshot_name
+                                                  *storage_parameter
+                                                  !%*storage_parameter
+                                                  !( refresh
+                                                     !(fast | complete | force)
+                                                     !(start with *date)
+                                                     !(next *date)
+                                                  )
            alter_snapshot_log                  =  alter
+                                                  snapshot
+                                                  log
+                                                  on
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  *storage_parameter
+                                                  !%*storage_parameter
            alter_system                        =  (enable | disable) restricted session
+                                               |  flush shared_pool
+                                               |  (checkpoint | check datafiles) !(global | local)
+                                               |  set *system_spec !%*system_spec
+                                               |  switch logfile
+                                               |  (enable | disable) distributed recovery
+                                               |  archive log *archive_log_spec
+                                               |  kill session *n $',' *n
            alter_table                         =  alter
+                                                  table
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  *alter_table_spec
+                                                  !%*alter_table_spec
            alter_table_spec                    =  add $'(' (*new_column_list | *new_constraint_list) $')'
+                                               |  modify $'(' *modified_column_list $')'
+                                               |  drop constraint $'(' *constraint_list $')'
+                                               |  *storage_parameter !%*storage_parameter
+                                               |  allocate extent !%*allocate_spec
+                                               |  enable *enable_spec
+                                               |  disable *disable_spec
            alter_tablespace                    =  alter
+                                                  tablespace
+                                                  *tablespace_name
+                                                  (  add datafile *file_spec_list
+                                                  |  rename datafile *file_list to *file_list
+                                                  |  default storage *storage_spec
+                                                  |  *system_status
+                                                  )
            alter_trigger                       =  alter trigger !(*schema_name $'.') *trigger_name (enable | disable)
            alter_user                          =  alter user *user_name *alter_user_spec !%*alter_user_spec
            alter_user_spec                     =  identified by *password
+                                               |  default tablespace *tablespace_name
+                                               |  temporary tablespace *tablespace_name
+                                               |  quota (*n k | m | unlimited) on *tablespace_name
+                                               |  profile *profile_name
+                                               |  default (*role_list | all !(except *role_list) | none)
            alter_view                          =  alter view !(*schema_name $'.') *view_name compile
            analyze_command                     =  analyze
+                                                  (  index !(*schema_name $'.') *index_name
+                                                  |  table !(*schema_name $'.') *table_name
+                                                  |  cluster !(*schema_name $'.') *cluster_name
+                                                  )
+                                                  *analyze_spec
            analyze_spec                        =  (compute | estimate !(sample *n (rows | percent)) | delete)
+                                                  statistics
+                                               |  validate structure !cascade
+                                               |  list chained rows !(into !(*schema_name $'.') *table_name)
            archive_log_spec                    =  !(thread *n) stop
+                                               |  (  seq *n
+                                                  |  change *n
+                                                  |  current
+                                                  |  group *n
+                                                  |  logfile $"'" *file_name $"'"
+                                                  |  next
+                                                  |  all
+                                                  |  start
+                                                  )
+                                                  !(to *location_name)
            audit_command                       =  *audit_sql | *audit_object
            audit_object                        =  audit
+                                                  (*obj_command !%($',' *command) | all)
+                                                  on
+                                                  (!(*schema_name $'.') *object_name | default)
+                                                  !(by (access | session))
+                                                  !(whenever !not successful)
            audit_sql                           =  audit
+                                                  (*stat_command !%($',' *stat_command) | all)
+                                                  !(by *user_list)
+                                                  !(by (access | session))
+                                                  !(whenever !not successful)
            binary_type                         =  raw $'(' *n $')' | rowid | long raw
            char_function                       =  chr
+                                               |  initcap
+                                               |  lower
+                                               |  lpad
+                                               |  ltrim
+                                               |  replace
+                                               |  rpad
+                                               |  rtrim
+                                               |  soundex
+                                               |  substr
+                                               |  translate
+                                               |  upper
+                                               |  ascii
+                                               |  instr
+                                               |  length
            char_set_name                       =  *identifier
            character_type                      =  (char | varchar | varchar2 | character | character varying)
+                                                  $'('
+                                                  *n
+                                                  $')'
+                                               |  long
            cluster_name                        =  *identifier
            column_constraint                   =  !(constraint *constraint_name) *def_column_constraint
            column_name                         =  *identifier
            comment_command                     =  comment
+                                                  on
+                                                  (  table !(*schema_name $'.') *relation_name
+                                                  |  column !(*schema_name $'.') *relation_name $'.' *column_name
+                                                  )
+                                                  is
+                                                  $"'"
+                                                  *string
+                                                  $"'"
            comparaison_op                      =  $'=' | $'<' | $'>' | $'<>' | $'!=' | $'^=' | $'<=' | $'>='
            condition                           =  !not *logical_term !%(or *logical_term)
            connect_clause                      =  connect
+                                                  by
+                                                  (  prior *exp_simple *comparaison_op *exp_simple
+                                                  |  *exp_simple *comparaison_op *exp_simple prior
+                                                  )
+                                                  !(start with *condition)
            constant                            =  *number | *quoted_string
            constraint_list                     =  *constraint_name !%($',' *constraint_name)
            controlfile_spec                    =  maxlogfiles *n
+                                               |  maxlogmembers *n
+                                               |  maxloghistory *n
+                                               |  maxdatafiles *n
+                                               |  maxinstances *n
+                                               |  archivelog
+                                               |  noarchivelog
            conversion_function                 =  chartorowid
+                                               |  convert
+                                               |  hextoraw
+                                               |  rawtohex
+                                               |  rowidtochar
+                                               |  to_char
+                                               |  to_date
+                                               |  to_number
            create_cluster                      =  create
+                                                  cluster
+                                                  !(*schema_name $'.')
+                                                  *cluster_name
+                                                  $'('
+                                                  *column_name
+                                                  *datatype
+                                                  !%($',' *column_name *datatype)
+                                                  $')'
+                                                  *create_cluster_spec
+                                                  !%*create_cluster_spec
            create_cluster_spec                 =  pctused *n
+                                               |  pctfree *n
+                                               |  size *n !(k | m)
+                                               |  initrans *n
+                                               |  maxtrans *n
+                                               |  tablespace *tablespace_name
+                                               |  storage $'(' *storage_spec !%*storage_spec $')'
+                                               |  index
+                                               |  !(hash is *column_name) hashkeys *n
            create_command                      =  *create_cluster
+                                               |  *create_controlfile
+                                               |  *create_database
+                                               |  *create_databaselink
+                                               |  *create_index
+                                               |  *create_profile
+                                               |  *create_role
+                                               |  *create_rollback
+                                               |  *create_schema
+                                               |  *create_sequence
+                                               |  *create_synonym
+                                               |  *create_snapshot
+                                               |  *create_snapshotlog
+                                               |  *create_table
+                                               |  *create_tablespace
+                                               |  *create_trigger
+                                               |  *create_user
+                                               |  *create_view
            create_controlfile                  =  create
+                                                  controlfile
+                                                  !reuse
+                                                  !set
+                                                  database
+                                                  *database_name
+                                                  logfile
+                                                  !%*group_file_spec
+                                                  resetlogs noresetlogs
+                                                  datafile
+                                                  *file_spec_list
+                                                  !%*controlfile_spec
            create_database                     =  create database !*database_name !%*create_database_spec
            create_database_spec                =  controlile reuse
+                                               |  logfile !%*group_file_spec
+                                               |  maxlogfiles *n
+                                               |  maxlogmembers *n
+                                               |  maxloghistory *n
+                                               |  datafile *file_spec_list
+                                               |  maxdatafiles *n
+                                               |  maxinstances *n
+                                               |  archivelog | noarchivelog
+                                               |  character set *char_set_name
+                                               |  exclusive
            create_databaselink                 =  create
+                                                  !public
+                                                  database
+                                                  link
+                                                  *link_name
+                                                  !(connect to *user_name identified by *password)
+                                                  using
+                                                  $"'"
+                                                  *connect_string
+                                                  $"'"
            create_index                        =  create
+                                                  index
+                                                  !(*schema_name $'.')
+                                                  *index_name
+                                                  on
+                                                  (  *table_name $'(' *indexed_column $')'
+                                                  |  cluster !(*schema_name $'.') *cluster_name
+                                                  )
+                                                  !%*index_storage
            create_profile                      =  create profile *profile_name limit *profile_spec !%*profile_spec
            create_role                         =  create
+                                                  role
+                                                  *role_name
+                                                  (not identified | identified (by *password | externally))
            create_rollback                     =  create
+                                                  !public
+                                                  rollback
+                                                  segment
+                                                  *rollback_name
+                                                  !(tablespace *tablespace_name)
+                                                  !(storage *storage_spec)
            create_schema                       =  create
+                                                  schema
+                                                  authorization
+                                                  *schema_name
+                                                  !%(*create_table | *create_view | *grant_command)
            create_sequence                     =  create
+                                                  sequence
+                                                  !(*schema_name $'.')
+                                                  *sequence_name
+                                                  *create_sequence_spec
+                                                  !%*create_sequence_spec
            create_sequence_spec                =  increment by *n
+                                               |  start with *n
+                                               |  maxvalue *n
+                                               |  nomaxvalue
+                                               |  minvalue *n
+                                               |  nominvalue
+                                               |  cycle | nocycle
+                                               |  cache *n
+                                               |  nocache
+                                               |  order | noorder
            create_snapshot                     =  $'create  '
+                                                  $'snapshot  '
+                                                  !(*schema_name $'. ')
+                                                  *snapshot_name
+                                                  !%*storage_parameter
+                                                  !(cluster *cluster_name $'(' *column_list $')')
+                                                  !( refresh
+                                                     !(fast | complete | force)
+                                                     !(start with *date)
+                                                     !(next *date)
+                                                  )
+                                                  !(as *query)
            create_snapshot_log                 =  create
+                                                  snapshot
+                                                  log
+                                                  on
+                                                  !(*schema_name $'.')
+                                                  *snapshot_name
+                                                  !%*storage_parameter
            create_synonym                      =  create
+                                                  !public
+                                                  synonym
+                                                  !(*schema_name $'.')
+                                                  *synonym
+                                                  for
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'@' *databaselink_name)
            create_table                        =  create
+                                                  table
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  $'('
+                                                  (*new_column_list | *new_constraint_list)
+                                                  $')'
+                                                  !%*storage_parameter
+                                                  !(cluster *cluster_name $'(' *column_list $')')
+                                                  !(enable *enable_spec)
+                                                  !(disable *disable_spec)
+                                                  !(as *query)
            create_tablespace                   =  create
+                                                  tablespace
+                                                  *tablespace_name
+                                                  !(datafile *file_spec_list)
+                                                  !(default storage $'(' *storage_spec !%*storage_spec $')')
+                                                  !(online | offline)
            create_trigger                      =  create
+                                                  !(or replace)
+                                                  trigger
+                                                  !(*schema_name $'.')
+                                                  *trigger_name
+                                                  *trigger_sync
+                                                  *trigger_ref
+                                                  *trigger_when
+                                                  *plsql_block
            create_user                         =  create
+                                                  user
+                                                  *user_name
+                                                  identified
+                                                  (by *password | externally)
+                                                  *create_user_spec
+                                                  !%*create_user_spec
            create_user_spec                    =  default tablespace *tablespace_name
+                                               |  temporary tablespace *tablespace_name
+                                               |  quota (*n k | m | unlimited) on *tablespace_name
+                                               |  profile *profile_name
            create_view                         =  create
+                                                  !(or replace)
+                                                  !(force | noforce)
+                                                  view
+                                                  !(*schema_name $'.')
+                                                  *view_name
+                                                  !($'(' *alias !%($',' *alias) $')')
+                                                  as
+                                                  *query
+                                                  !(with check option !(constraint *constraint_name))
            database_name                       =  *identifier
            datatype                            =  *character_type
+                                               |  *date_type
+                                               |  *float_type
+                                               |  *decimal_type
+                                               |  *integer_type
+                                               |  *binary_type
            date_format                         =  *quoted_string
            date_function                       =  add_months
+                                               |  last_day
+                                               |  months_between
+                                               |  new_time
+                                               |  next_day
+                                               |  round
+                                               |  sysdate
+                                               |  trunc
            date_type                           =  date
            decimal_type                        =  number $'(' *n $',' *n $')'
+                                               |  decimal $'(' *n $',' *n $')'
+                                               |  dec $'(' *n $',' *n $')'
+                                               |  numeric $'(' *n $',' *n $')'
            def_column_constraint               =  !not null
+                                               |  unique | primary key
+                                               |  references
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'(' *column_name $')')
+                                                  !(on delete cascade)
+                                               |  chek $'(' *condition $')'
+                                               |  !(using index *index_storage !%*index_storage)
+                                                  !(exceptions into !(*schema_name $'.') *table_name)
+                                               |  disable
            def_table_constraint                =  (unique | primary key) $'(' *column_list $')'
+                                               |  foreign
+                                                  key
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  references
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'(' *column_list $')')
+                                                  !(on delete cascade)
+                                               |  chek $'(' *condition $')'
+                                               |  !(using index *index_storage !%*index_storage)
+                                                  !(exceptions into !(*schema_name $'.') *table_name)
+                                               |  disable
            delete_command                      =  delete
+                                                  from
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'@' *link_name)
+                                                  !(where *condition)
            disable_spec                        =  (unique | primary key | constraint *constraint_name) !cascade
+                                               |  all triggers
            displayed_column                    =  !(*schema_name $'.') *table_name $'.' $'*' | *exp_simple !*alias
            distribution_list                   =  (*user_name | *role_name | public)
+                                                  !%($',' (*user_name | *role_name | public))
            domain_name                         =  *identifier
            drop_cluster                        =  drop
+                                                  cluster
+                                                  !(*schema_name $'.')
+                                                  *cluster_name
+                                                  !(including tables)
+                                                  !(cascade constraints)
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
            drop_databaselink                   =  drop !public database link *link_name
            drop_index                          =  drop index !(*schema_name $'.') *index_name
            drop_profile                        =  drop profile *profile_name !cascade
            drop_role                           =  drop role *role_name
            drop_rollback                       =  drop rollback segment *rollback_name
            drop_sequence                       =  drop sequence !(*schema_name $'.') *sequence_name
            drop_snapshot                       =  drop snapshot !(*schema_name $'.') *snapshot_name
            drop_snapshotlog                    =  drop snapshot log on !(*schema_name $'.') *table_name
            drop_synonym                        =  drop !public synonym !(*schema_name $'.') *synonym
            drop_table                          =  drop table !(*schema_name $'.') *table_name !(cascade constraints)
            drop_tablespace                     =  drop
+                                                  tablespace
+                                                  *tablespace_name
+                                                  !(including contents)
+                                                  !(cascade constraints)
            drop_trigger                        =  drop trigger !(*schema_name $'.') *trigger_name
            drop_user                           =  drop user *user_name !cascade
            drop_view                           =  drop view !(*schema_name $'.') *view_name
            enable_spec                         =  (  unique $'(' *column_list $')'
+                                                  |  primary key
+                                                  |  constraint *constraint_name
+                                                  )
+                                                  !(using index *index_storage !%*index_storage)
+                                                  !(exceptions into !(*schema_name $'.') *table_name)
+                                               |  all triggers
            exp_set                             =  (*number | *quoted_string) !%($',' (*number | *quoted_string))
+                                               |  *subquery
            explain_command                     =  explain
+                                                  plan
+                                                  !(set statement_id $'=' *quoted_string)
+                                                  !(into !(*schema_name $'.') *table_name !($'@' *link_name))
+                                                  for
+                                                  (  *select_command
+                                                  |  *insert_command
+                                                  |  *update_command
+                                                  |  *delete_command
+                                                  )
            expression                          =  !($'+' | $'-') *term !%(($'+' | $'-') *term)
            factor                              =  *constante_nonsigne
+                                               |  *variable
+                                               |  *function !($'(' *expression !%($',' *expression) $')')
+                                               |  *group_function $'(' !($'*' | all | distinct) *expression $')'
            file_list                           =  $"'" *file_name $"'" !%($',' $"'" *file_name $"'")
            file_name                           =  *file_name_in_your_system
            file_reuse                          =  $"'" *file_name $"'" !reuse
            file_reuse_list                     =  *file_reuse !%($',' *file_reuse)
            file_spec                           =  $"'" *file_name $"'" !(size *n !(k | m)) !reuse
            file_spec_list                      =  *file_spec !%($',' *file_spec)
            file_spec_redo                      =  ($"'" *file_name $"'" | $'(' *file_list $')')
+                                                  !(size *n !(k | m))
+                                                  !reuse
            float_type                          =  number | float | real | double precision
            function                            =  *number_function
+                                               |  *char_function
+                                               |  *group_function
+                                               |  *conversion_function
+                                               |  *other_function
            grant_command                       =  *grant_priv | *grant_object
            grant_object                        =  grant
+                                                  (*privilege !%($',' *privilege) | all !privilege)
+                                                  !($'(' *column_list $')')
+                                                  on
+                                                  !(*schema_name $'.') object_name
+                                                  to
+                                                  *distribution_list
+                                                  !(with grant option)
            grant_priv                          =  grant
+                                                  *priv_granted !%($',' *priv_granted)
+                                                  to
+                                                  *distribution_list
+                                                  !(with admin option)
            group_clause                        =  group by *expression !%($',' *expression) !(having *condition)
            group_file                          =  group *n | $"'" *file_name $"'" | $'(' *file_list $')'
            group_file_list                     =  *group_file !%($',' *group_file)
            group_file_spec                     =  !(group *n) *file_spec_redo
            group_function                      =  avg | count | max | min | stddev | sum | variance
            identifier                          =  letter !%(letter | digit | underline | dollar | sharp)
+                                               |  quote !%$'any character' quote
            index_name                          =  *identifier
            index_storage                       =  pctfree *n
+                                               |  initrans *n
+                                               |  maxtrans *n
+                                               |  tablespace *tablespace_name
+                                               |  storage $'(' *storage_spec !%*storage_spec $')'
+                                               |  nosort
            indexed_column_list                 =  *column_name !(asc | desc) !%(*column_name !(asc | desc))
            insert_command                      =  insert
+                                                  into
+                                                  !(*schema_name $'.') (*table_name | *view_name) !($'@' *link_name)
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  ($'(' *value_list $')' | *query)
            integer_type                        =  number $'(' *n $')' | integer | int | smallint
            language_name                       =  *identifier
            link_name                           =  *identifier
            location_name                       =  *quoted_string
            lock_command                        =  lock
+                                                  table
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'@' *link_name)
+                                                  !%($',' !(*schema_name $'.') *table_name !($'@' *link_name))
+                                                  in
+                                                  *lock_mode
+                                                  mode
+                                                  !nowait
            lock_mode                           =  share
+                                               |  exclusive
+                                               |  row (share | exclusive)
+                                               |  share (update | row exclusive)
            logfile_clause                      =  !(thread *n) *group_file_spec !%($',' *group_file_spec)
            logical_factor                      =  *exp_simple *comparaison_op *exp_simple
+                                               |  !not in *exp_set
+                                               |  !not like *match_string
+                                               |  !not between *exp_simple and *exp_simple
+                                               |  is !not null
+                                               |  *quantified_factor
+                                               |  $'(' *condition $')'
            logical_term                        =  *logical_factor !%(and *logical_factor)
            logmember_clause                    =  *file_reuse_list to *group_file
            match_string                        =  $"'" !%(any_character | _ | $'%') $"'"
            modified_column_list                =  *column_name
+                                                  !*datatype
+                                                  !(default *expression)
+                                                  !%*column_constraint
+                                                  !%(
+                                                     $','
+                                                     *column_name
+                                                     !*datatype
+                                                     !(default *expression)
+                                                     !%*column_constraint
+                                                  )
            n                                   =  digit !%digit
            new_column_list                     =  *column_name
+                                                  *datatype
+                                                  !(default *expression)
+                                                  !%*column_constraint
+                                                  !%(
+                                                     $','
+                                                     *column_name
+                                                     *datatype
+                                                     !(default *expression)
+                                                     !%*column_constraint
+                                                  )
            new_constraint_list                 =  *table_constraint !%($',' *table_constraint)
            new_name                            =  *identifier
            noaudit_command                     =  *noaudit_sql | *noaudit_object
            noaudit_object                      =  noaudit
+                                                  (*obj_command !%($',' *command) | all)
+                                                  on
+                                                  (!(*schema_name $'.') *object_name | default)
+                                                  !(by (access | session))
+                                                  !(whenever !not successful)
            noaudit_sql                         =  noaudit
+                                                  (*stat_command !%($',' *stat_command) | all)
+                                                  !(by *user_list)
+                                                  !(by (access | session))
+                                                  !(whenever !not successful)
            number                              =  *n !($'.' !*n) !(E !($'+' | $'-') *n)
            number_function                     =  abs | ceil | floor | mod | power | round | sign | sqrt | trunc
            obj_command                         =  *table_command
+                                               |  *view_command
+                                               |  *sequence_command *prog_command
+                                               |  *snapshot_commandd
            object_name                         =  *identifier
            old_name                            =  *identifier
            order_clause                        =  order by *sorted_def !%($',' *sorted_def)
            other_function                      =  decode | dump | greatest | least | nvl | uid | user | userenv | vsize
            partition_name                      =  *identifier
            pass_role_list                      =  *role_name
+                                                  !(identified by *password)
+                                                  !%($',' *role_name !(identified by *password))
            password                            =  *identifier
            privilege                           =  *table_privilege
+                                               |  *view_privilege
+                                               |  *sequence_privilege *prog_privilege
+                                               |  *snapshot_privilege
            profile_name                        =  *identifier
            profile_spec                        =  *resource_name (*n | unlimited | default)
+                                               |  private_sga (*n !(k | m) | unlimited | default)
            prog_command                        =  execute | audit | grant | rename
            prog_privilege                      =  execute
            quantified_factor                   =  *exp_simple *comparaison_op !(all | any) *subquery
+                                               |  !not exists *subquery
            query                               =  *select_command
            quoted_string                       =  $"'" !%any_character $"'"
            recover_clause                      =  recover
+                                                  !automatic
+                                                  !(from $"'" *file_name $"'")
+                                                  (  !database !*until_spec
+                                                  |  tablespace *tablespace_list
+                                                  |  datafile *file_list
+                                                  |  logfile *file_name
+                                                  |  continue !default
+                                                  |  cancel
+                                                  )
            relation_name                       =  *table_name | *view_name | *snapshot_name
            rename_command                      =  rename *old_name to *new_name
            resource_cost_name                  =  cpu_per_session | connect_time | private_sga
            resource_name                       =  sessions_per_user
+                                               |  cpu_per_session
+                                               |  cpu_per_call
+                                               |  connect_time
+                                               |  idle_time
+                                               |  logical_reads_per_session
+                                               |  logical_reads_per_call
+                                               |  composite_limit
            revoke_command                      =  *revoke_priv | *revoke_object
            revoke_object                       =  revoke
+                                                  (*privilege !%($',' *privilege) | all !privilege)
+                                                  on
+                                                  !(*schema_name $'.') object_name
+                                                  to
+                                                  *distribution_list
+                                                  !(cascade constraints)
            revoke_priv                         =  revoke *priv_granted !%($',' *priv_granted) from *distribution_list
            role_list                           =  *role_name !%($',' *role_name)
            rollback_name                       =  *identifier
            savepoint_name                      =  *identifier
            schema_name                         =  *identifier
            select_command                      =  select
+                                                  !(all | distinct)
+                                                  ($'*' | *displayed_column !%($',' *displayed_column))
+                                                  from
+                                                  *selected_table !%($',' *selected_table)
+                                                  !(where *condition)
+                                                  !%*connect_clause
+                                                  !%*group_clause
+                                                  !%*set_clause
+                                                  !%*order_clause
+                                                  !%*update_clause
            selected_table                      =  !(*schema_name $'.') *table_name !($'@' *link_name) !*alias
            self                                =  *identifier
            sequence_command                    =  alter | audit | grant | select
            sequence_name                       =  *identifier
            sequence_privilege                  =  alter | select
            set_clause                          =  (union all | intersect | minus) *select_command
            set_role_command                    =  set role (*pass_role_list | all !(*except *role_list) | none)
            set_session_spec                    =  (sql_trace | global_names) $'=' (true | false)
+                                               |  nls_language $'=' *language_name
+                                               |  nls_territory $'=' *territory_name
+                                               |  nls_date_format $'=' *date_format
+                                               |  nls_date_language $'=' *language_name
+                                               |  nls_numeric_character $'=' *quoted_string
+                                               |  nls_iso_currency $'=' *territory_name
+                                               |  nls_currency $'=' *quoted_string
+                                               |  nls_sort $'=' (*sort_name | binary)
+                                               |  optimizer goal $'=' (all_rows | first_rows | choose | rule)
            set_transaction_command             =  set
+                                                  transaction
+                                                  (read only | read write | use rollback segment *rollback_name)
            simple_update                       =  update
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !($'@' *link_name)
+                                                  !*alias
+                                                  set
+                                                  *column
+                                                  $'='
+                                                  (*expression | *subquery)
+                                                  !%($',' *column $'=' (*expression | *subquery))
+                                                  where
+                                                  *condition
            snapshot_command                    =  select
            snapshot_name                       =  *identifier
            snapshot_privilege                  =  select
            sorted_def                          =  (*expression | *n) (asc | desc)
            stat_command                        =  *statement_opt | *system_priv
            statement_opt                       =  cluster
+                                               |  $'database link'
+                                               |  exists
+                                               |  index
+                                               |  $'not exists'
+                                               |  procedure
+                                               |  profile
+                                               |  $'...'
+                                               |  $'see table 4_7 of SQL ref. manual'
            storage_parameter                   =  pctfree *n
+                                               |  pctused *n
+                                               |  initrans *n
+                                               |  maxtrans *n
+                                               |  storage $'(' *storage_spec !%*storage_spec $')'
            storage_spec                        =  initial *n !(k | m)
+                                               |  next *n !(k | m)
+                                               |  minextents *n
+                                               |  maxextents *n
+                                               |  pctincrease *n
+                                               |  optimal (null | *n !(k | m))
+                                               |  freelist *n
+                                               |  freelist groups *n
            subquery                            =  $'(' *select_command $')'
            subquery_update                     =  update
+                                                  !(*schema_name $'.')
+                                                  *table_name
+                                                  !*alias
+                                                  !($'@' *link_name)
+                                                  set
+                                                  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
+                                                  $'='
+                                                  *subquery
+                                                  where
+                                                  *condition
            synonym                             =  *identifier
            system_priv                         =  $'alter any cluster'
+                                               |  $'alter any index'
+                                               |  $'alter any procedure'
+                                               |  $'alter any role'
+                                               |  $'alter any sequence'
+                                               |  $'alter any snapshot'
+                                               |  $'alter any table'
+                                               |  $'...'
+                                               |  $'see table 4_11 of SQL ref. manual'
            system_spec                         =  (resource_limit | global_names) $'=' (true | false)
+                                               |  mts_servers $'=' *n
+                                               |  mts_dispatcher $'=' *protocol $',' *n
+                                               |  license_max_session $'=' *n
+                                               |  license_session_warning $'=' *n
+                                               |  license_max_users $'=' *n
            system_status                       =  (online | offline) !(normal | temporary | immediate)
+                                               |  (begin | end) backup
            table_command                       =  alter
+                                               |  audit
+                                               |  comment
+                                               |  delete
+                                               |  grant
+                                               |  index
+                                               |  insert
+                                               |  lock
+                                               |  rename
+                                               |  select
+                                               |  update
            table_constraint                    =  !(constraint *constraint_name) *def_table_constraint
            table_name                          =  *identifier
            table_privilege                     =  alter | delete | index | insert | references | select | update
            tablespace_list                     =  *tablespace_name !%($',' *tablespace_name)
            tablespace_name                     =  *identifier
            term                                =  *factor !%(($'*' | $'/') *factor)
            territory_name                      =  *identifier
            to_control_data                     =  *audit_command
+                                               |  *noaudit_command
+                                               |  *grant_command
+                                               |  *revoke_command
+                                               |  *set_role_command
            to_define_data                      =  *alter_command
+                                               |  *comment_command
+                                               |  *create_command
+                                               |  *drop_command
+                                               |  *rename_command
+                                               |  *analyze_command
+                                               |  *explain_command
            to_modify_data                      =  *select_command
+                                               |  *insert_command
+                                               |  *update_command
+                                               |  *delete_command
+                                               |  *truncate_command
+                                               |  *transaction_command
+                                               |  *set_transaction_command
+                                               |  *lock_command
            transaction_command                 =  commit
+                                                  !work
+                                                  !(comment *quoted_string | force *quoted_string !($',' *n))
+                                               |  set transaction read only
+                                               |  savepoint *savepoint_name
+                                               |  rollback
+                                                  !work
+                                                  !(to !(savepoint *savepoint_name) | force *quoted_string)
            trigger_name                        =  *identifier
            trigger_ref                         =  referencing !(old !as *identifier) !(new !as *identifier)
            trigger_sync                        =  (before | after)
+                                                  (delete | insert | update !(of *column_list))
+                                                  !%(or (delete | insert | update !(of *column_list)))
+                                                  on
+                                                  !(*schema_name $'.')
+                                                  *table_name
            trigger_when                        =  for each row !(when $'(' *condition $')')
            truncate_command                    =  truncate
+                                                  (  table !(*schema_name $'.') *table_name
+                                                  |  cluster !(*schema_name $'.') *cluster_name
+                                                  )
+                                                  !((drop | reuse) storage)
            until_spec                          =  until (cancel | time *date | change *n) | using backup controlfile
            update_clause                       =  for update of *column_name !%($',' *column_name) !nowait
            update_command                      =  *simple_update | *subquery_update
            user_list                           =  *user_name !%($',' *user_name)
            user_name                           =  *identifier
            value                               =  !($'+' | $'-') (*identifier | *n) | *quoted_string
            value_list                          =  values $'(' *value !%($',' *value)
            variable                            =  !(*table_name $'.') *column_name !$'(+)'
            view_command                        =  audit
+                                               |  comment
+                                               |  delete
+                                               |  grant
+                                               |  insert
+                                               |  lock
+                                               |  rename
+                                               |  select
+                                               |  update
            view_name                           =  *identifier
            view_privilege                      =  delete | insert | select | update
            alter_function                      =  alter function !(*schema_name $'.') *function_name compile
            alter_package                       =  alter
+                                                  package
+                                                  !(*schema_name $'.')
+                                                  *package_name
+                                                  compile
+                                                  !(package | body)
            alter_procedure                     =  alter procedure !(*schema_name $'.') *procedure_name compile
            argument                            =  *argument_name
+                                                  !(in | out | in out)
+                                                  *argument_type
+                                                  !($':=' default *plsql_value)
            argument_name                       =  *identifier
            argument_type                       =  *type_spec
            assignment_statement                =  *object $':=' *plsql_expression $';'
            boolean_exp                         =  !not *boolean_term !%(or *boolean_term)
            boolean_factor                      =  *boolean_literal
+                                               |  *variable_name
+                                               |  *plsql_function !($'(' *plsql_exp_list $')')
+                                               |  $'(' *boolean_exp $')'
+                                               |  *plsql_expression
+                                                  (  *relational_op *plsql_expression
+                                                  |  is !not null
+                                                  |  !not like *match_string
+                                                  |  !not between *plsql_expression and *plsql_expression
+                                                  |  !not in $'(' *plsql_exp_list $')'
+                                                  |  (*cursor_name | *subquery)
+                                                     ($'%notfound' | $'%found' | $'%isopen')
+                                                  )
            boolean_literal                     =  true | false | null
            boolean_term                        =  *boolean_factor !%(and *boolean_factor)
            char_expression                     =  *char_term !%($'||' *char_term)
            char_literal                        =  *quoted_string
            char_term                           =  *char_literal
+                                               |  *variable_name
+                                               |  *host_variable
+                                               |  *plsql_function !($'(' *plsql_exp_list $')')
+                                               |  $'(' *char_expression $')'
+                                               |  null
            close_statement                     =  close *cursor_name
            column_list                         =  *column_name !%($',' *column_name)
            comment                             =  $'--' text_until_end_of_line | $'/*' multi_line_text $'*/'
            commit_statement                    =  commit !work !(comment *quoted_string)
            create_function                     =  create !(or replace) *function_declaration
            create_package                      =  create !(or replace) (*package_spec | *package_body)
            create_procedure                    =  create !(or replace) *procedure_declaration
            cursor_body                         =  cursor
+                                                  *cursor_name
+                                                  !($'(' *parameter_spec !%($',' *parameter_spec) $')')
+                                                  return
+                                                  *return_type
+                                                  is
+                                                  *select_statement
+                                                  $';'
            cursor_declaration                  =  cursor
+                                                  *cursor_name
+                                                  !($'(' *parameter_spec !%($',' *parameter_spec) $')')
+                                                  is
+                                                  *select_statement
+                                                  $';'
            cursor_loop_param                   =  *record_name
+                                                  in
+                                                  (  *cursor_name !($'(' *plsql_exp_list $')')
+                                                  |  $'(' *select_statement $')'
+                                                  )
            cursor_name                         =  *identifier
            cursor_spec                         =  cursor
+                                                  *cursor_name
+                                                  !($'(' *parameter_spec !%($',' *parameter_spec) $')')
+                                                  return
+                                                  *return_type
+                                                  $';'
            plsql_datatype                      =  binary_integer
+                                               |  natural
+                                               |  positive
+                                               |  number !($'(' *n !($',' *n) $')')
+                                               |  char !($'(' *n $')')
+                                               |  long
+                                               |  raw
+                                               |  long raw
+                                               |  boolean
+                                               |  date
            date_expression                     =  *date_literal
+                                               |  *variable_name
+                                               |  *host_variable
+                                               |  *plsql_function !($'(' *plsql_exp_list $')')
+                                               |  $'(' *date_expression $')'
+                                               |  null
            date_literal                        =  *quoted_string
            declare_spec                        =  *variable_declaration
+                                               |  *subtype_declaration
+                                               |  *cursor_declaration
+                                               |  *exception_declaration
+                                               |  *exception_pragma
+                                               |  *record_declaration
+                                               |  *plsql_table_declaration
+                                               |  *procedure_declaration
+                                               |  *function_declaration
            delete_statement                    =  delete
+                                                  from
+                                                  *table_reference
+                                                  !*alias
+                                                  !(where *condition | current of *cursor_name)
            drop_function                       =  drop !(*schema_name $'.') *procedure_name
            drop_package                        =  drop !(*schema_name $'.') *package_name
            drop_procedure                      =  drop !(*schema_name $'.') *procedure_name
            error_number                        =  !($'+' | $'-') *n
            exception_declaration               =  *exception_name exception $';'
            exception_handler                   =  when
+                                                  (*exception_name !%(or *exception_name) | others)
+                                                  then
+                                                  *seq_of_statements
            exception_name                      =  *identifier
            exception_pragma                    =  pragma
+                                                  exception_init
+                                                  $'('
+                                                  *exception_name
+                                                  $','
+                                                  *error_number
+                                                  $')'
+                                                  $';'
            exit_statement                      =  exit !*label_name !(when *plsql_condition)
            fetch_statement                     =  fetch
+                                                  *cursor_name
+                                                  into
+                                                  (*variable_name !%($',' *variable_name) | *record_name)
            field_name                          =  *identifier
            field_spec                          =  *field_name *type_spec !(not null)
            plsql_function                      =  $'all functions' | sqlcode | sqlerrm
            function_body                       =  function
+                                                  *function_name
+                                                  $'('
+                                                  *argument
+                                                  !%($',' *argument)
+                                                  $')'
+                                                  return
+                                                  *return_type
+                                                  is
+                                                  !(declare *declare_spec $';' !%(*declare_spec $';'))
+                                                  begin
+                                                  *seq_of_statements
+                                                  !(exception *exception_handler !%*exception_handler)
+                                                  end
+                                                  !*function_name
+                                                  $';'
            function_declaration                =  *function_body
            function_name                       =  !(*schema_name $'.') *identifier
            function_spec                       =  function
+                                                  *function_name
+                                                  $'('
+                                                  *argument
+                                                  !%($',' *argument)
+                                                  $')'
+                                                  return
+                                                  *return_type
+                                                  $';'
            goto_statement                      =  goto !*label_name
            host_variable                       =  *identifier
            if_statement                        =  if
+                                                  *plsql_condition
+                                                  then
+                                                  *seq_of_statements
+                                                  !%(elsif *plsql_condition then *seq_of_statements)
+                                                  !(else *seq_of_statements)
+                                                  end
+                                                  if
            insert_statement                    =  insert
+                                                  into
+                                                  *table_reference
+                                                  !($'(' *column_list $')')
+                                                  (values $'(' *plsql_exp_list $')' | *select_statement)
            integer_expr                        =  *num_expression
            label_name                          =  *identifier
            lock_table_statement                =  lock table *table_reference in *lock_mode mode !nowait
            loop_statement                      =  !*label_name
+                                                  !( while *plsql_condition
+                                                  |  for (*numeric_loop_param | *cursor_loop_param)
+                                                  )
+                                                  loop
+                                                  *seq_of_statements
+                                                  end
+                                                  loop
+                                                  !*label_name
            null_statement                      =  null
            num_expression                      =  !($'+' | $'-') *num_term !%(($'+' | $'-') *num_term)
            num_factor                          =  (  *numeric_literal
+                                                  |  *variable_name
+                                                  |  *host_variable
+                                                  |  *plsql_function !($'(' *plsql_exp_list $')')
+                                                  |  $'(' *num_expression $')'
+                                                  |  null
+                                                  |  (*cursor_name | *subquery) $'%rowcount'
+                                                  )
+                                                  !($'**' *integer_expr)
            num_term                            =  *num_factor !%(($'*' | $'/') *num_factor)
            numeric_literal                     =  *number
            numeric_loop_param                  =  *index_name in !reverse *integer_expr $'..' *integer_expr
            object                              =  *variable_name
+                                               |  *record_name $'.' *field_name
+                                               |  *plsql_table_name $'(' *subscript $')'
+                                               |  $':' *host_variable
            open_statement                      =  open *cursor_name !($'(' *plsql_exp_list $')')
            package_body                        =  package
+                                                  *package_name
+                                                  is
+                                                  *package_obj_body
+                                                  !%*package_obj_body
+                                                  !(begin *seq_of_statements)
+                                                  end
+                                                  !*package_name
+                                                  $';'
            package_name                        =  !(*schema_name $'.') *identifier
            package_obj_body                    =  *variable_declaration
+                                               |  *subtype_declaration
+                                               |  *cursor_declaration
+                                               |  *cursor_body
+                                               |  *exception_declaration
+                                               |  *record_declaration
+                                               |  *plsql_table_declaration
+                                               |  *procedure_body
+                                               |  *function_body
            package_obj_spec                    =  *variable_declaration
+                                               |  *subtype_declaration
+                                               |  *cursor_declaration
+                                               |  *cursor_spec
+                                               |  *exception_declaration
+                                               |  *record_declaration
+                                               |  *plsql_table_declaration
+                                               |  *procedure_spec
+                                               |  *reference_pragma
+                                               |  *function_spec
            package_spec                        =  package
+                                                  *package_name
+                                                  is
+                                                  *package_obj_spec
+                                                  !%*package_obj_spec
+                                                  end
+                                                  !*package_name
+                                                  $';'
            parameter_name                      =  *identifier
            parameter_spec                      =  *parameter_name *plsql_datatype
            plsql_block                         =  !($'<<' *label_name $'>>')
+                                                  !(declare *declare_spec !%*declare_spec)
+                                                  begin
+                                                  *seq_of_statements
+                                                  !(exception *exception_handler !%*exception_handler)
+                                                  end
+                                                  !*label_name
+                                                  $';'
            plsql_condition                     =  *boolean_exp
            plsql_exp_list                      =  *plsql_expression !%($',' *plsql_expression)
            plsql_expression                    =  *num_expression
+                                               |  *char_expression
+                                               |  *date_expression
+                                               |  *boolean_expression
            plsql_store_in_db                   =  *alter_function
+                                               |  *alter_package
+                                               |  *alter_procedure
+                                               |  *create_function
+                                               |  *create_package
+                                               |  *create_procedure
+                                               |  *create_trigger
+                                               |  *drop_function
+                                               |  *drop_package
+                                               |  *drop_procedure
            plsql_table_declaration             =  *table_type_dec | *table_var_dec
            plsql_table_name                    =  *identifier
            procedure_body                      =  procedure
+                                                  *procedure_name
+                                                  !($'(' *argument !%($',' *argument) $')')
+                                                  return
+                                                  *return_type
+                                                  is
+                                                  !(declare *declare_spec $';' !%(*declare_spec $';'))
+                                                  begin
+                                                  *seq_of_statements
+                                                  !(exception *exception_handler !%*exception_handler)
+                                                  end
+                                                  !*procedure_name
+                                                  $';'
            procedure_declaration               =  *procedure_body
            procedure_name                      =  !(*schema_name $'.') *identifier
            procedure_spec                      =  procedure
+                                                  *procedure_name
+                                                  !($'(' *argument !%($',' *argument) $')')
+                                                  $';'
            raise_statement                     =  raise !*exception_name
            record_declaration                  =  *record_type_dec | *record_var_dec
            record_name                         =  *identifier
            record_type_dec                     =  type
+                                                  *type_name
+                                                  is
+                                                  record
+                                                  $'('
+                                                  *field_spec
+                                                  !%($',' *field_spec)
+                                                  $')'
+                                                  $';'
            record_var_dec                      =  *record_name *type_name $';'
            reference_pragma                    =  pragma
+                                                  restrict_reference
+                                                  $'('
+                                                  *function_name
+                                                  $','
+                                                  wnds
+                                                  !($',' wnps)
+                                                  !($',' rnds)
+                                                  !($',' rnps)
+                                                  $')'
+                                                  $';'
            relational_op                       =  $'=' | $'<' | $'>' | $'<>' | $'!=' | $'^=' | $'<=' | $'>='
            return_statement                    =  return !*plsql_expression
            return_type                         =  *type_spec
            rollback_statement                  =  rollback
+                                                  !work
+                                                  !(to !savepoint *savepoint_name)
+                                                  !(comment *quoted_string)
            savepoint_statement                 =  savepoint *savepoint_name
            select_statement                    =  select
+                                                  *sql_item
+                                                  !%($',' *sql_item)
+                                                  into
+                                                  (*variable_name !%($',' *variable_name) | *record_name)
+                                                  from
+                                                  *table_reference !%($',' *table_reference)
+                                                  *sql_rest_of_select
            seq_of_statements                   =  *statement $';' !%(*statement $';')
            set_transaction_statement           =  set transaction read only
            plsql_simple_update                 =  update
+                                                  *table_reference
+                                                  set
+                                                  *column_name
+                                                  $'='
+                                                  (*sql_expression | *sql_subquery)
+                                                  !%($',' *column_name $'=' (*sql_expression | *sql_subquery))
+                                                  !(where *condition | current of *cursor_name)
            sql_item                            =  $'as in sql select_command'
            sql_rest_of_select                  =  $'as in sql select_command'
            sql_statement                       =  *close_statement
+                                               |  *commit_statement
+                                               |  *delete_statement
+                                               |  *fetch_statement
+                                               |  *insert_statement
+                                               |  *lock_table_statement
+                                               |  *open_statement
+                                               |  *rollback_statement
+                                               |  *savepoint_statement
+                                               |  *select_statement
+                                               |  *set_transaction_statement
+                                               |  *update_statement
            sql_subquery                        =  $'as in sql select_command'
            statement                           =  *comment
+                                               |  *assignment_statement
+                                               |  *exit_statement
+                                               |  *goto_statement
+                                               |  *if_statement
+                                               |  *loop_statement
+                                               |  *null_statement
+                                               |  *raise_statement
+                                               |  *return_statement
+                                               |  *sql_statement
+                                               |  *plsql_block
            plsql_subquery_update               =  update
+                                                  *table_reference
+                                                  set
+                                                  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
+                                                  $'='
+                                                  *sql_subquery
+                                                  !(where *condition | current of *cursor_name)
            subscript                           =  *plsql_expression
            subtype_declaration                 =  subtype *type_name is *type_spec $';'
            table_type_dec                      =  type
+                                                  *type_name
+                                                  is
+                                                  table
+                                                  of
+                                                  *field_spec
+                                                  indexed
+                                                  by
+                                                  binary_integer
+                                                  $';'
            table_var_dec                       =  *plsql_table_name *type_name $';'
            type_name                           =  *identifier
            type_spec                           =  *plsql_datatype
+                                               |  *variable_name $'%type'
+                                               |  *table_name $'.' *column_name $'%type'
+                                               |  *table_name $'%rowtype'
+                                               |  *type_name
            update_statement                    =  *plsql_simple_update | *plsql_subquery_update
            plsql_value                         =  !($'+' | _) *number | *quoted_string
            variable_declaration                =  *variable_name
+                                                  !constant
+                                                  *type_name
+                                                  !(not null)
+                                                  !(($':=' | default) *plsql_expression)
+                                                  $';'
            variable_name                       =  *identifier
            variable_type                       =  *type_spec

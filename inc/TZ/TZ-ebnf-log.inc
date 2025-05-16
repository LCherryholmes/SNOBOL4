            ident                               =  *IDENT | log
            number                              =  *NUMBER
            string                              =  *SQ_STRING | *DQ_STRING
            alias                               =  *IDENT | *DQ_STRING
            column_name                         =  *ident
            constraint_name                     =  *ident
            cursor_name                         =  *ident
            database_device                     =  *ident | *local_variable
            database_name                       =  *ident | *local_variable
            index_name                          =  *ident
            row_aggregate                       =  *ident
            savepoint_name                      =  *ident
            segment_name                        =  *ident | *local_variable
            server_name                         =  *ident
            table_name                          =  *ident
            transaction_name                    =  *ident
            time                                =  *string
            return_status                       =  *at_ident
            parameter                           =  *at_ident
            local_variable                      =  *at_ident
            global_variable                     =  *at_at_ident
            error_number                        =  *NUMBER
            extended_value                      =  *NUMBER
            size                                =  *NUMBER
            x                                   =  *NUMBER
            column_name_list                    =  *column_name | *column_name_list $',' *column_name
            database_name_list                  =  *database_name | *database_name_list $',' *database_name
            owner_object_list                   =  *owner_object | *owner_object_list $',' *owner_object
            owner_object                        =  *ident | *ident $'.' *ident
            server_procedure                    =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $'.' $'.' $'.' *ident
+                                               |  *ident $'.' $'.' *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident $'.' *ident
            table                               =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            table_or_view                       =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            view                                =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            column                              =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident $'.' *ident
            eos                                 =  go
            statements                          =  *eos
+                                               |  *execute_command *eos
+                                               |  *execute_command *SQL_statements *eos
+                                               |  *SQL_statements *eos
+                                               |  *SQL_nonbatch_statement *eos
+                                               |  *statements *eos
+                                               |  *statements *execute_command *eos
+                                               |  *statements *execute_command *SQL_statements *eos
+                                               |  *statements *SQL_statements *eos
+                                               |  *statements *SQL_nonbatch_statement *eos
            SQL_nonbatch_statement              =  *create_default_statement
+                                               |  *create_procedure_statement
+                                               |  *create_rule_statement
+                                               |  *create_trigger_statement
+                                               |  *create_view_statement
            SQL_statements                      =  *SQL_statement | *SQL_statements *SQL_statement
            SQL_statement                       =  *SQL_matched_statement | *SQL_unmatched_statement
            SQL_unmatched_statement             =  if *logical_expr *SQL_statement
+                                               |  if
+                                                  *logical_expr
+                                                  *SQL_matched_statement
+                                                  else
+                                                  *SQL_unmatched_statement
            SQL_matched_statement               =  if *logical_expr *SQL_matched_statement else *SQL_matched_statement
+                                               |  *SQL_command_statement
            SQL_command_statement               =  *alter_database_statement
+                                               |  *alter_table_statement
+                                               |  *begin_statement
+                                               |  *begin_transaction_statement
+                                               |  *break_statement
+                                               |  *checkpoint_statement
+                                               |  *close_statement
+                                               |  *commit_transaction_statement
+                                               |  *continue_statement
+                                               |  *create_database_statement
+                                               |  *create_index_statement
+                                               |  *create_table_statement
+                                               |  *dbcc_statement
+                                               |  *deallocate_cursor_statement
+                                               |  *declare_cursor_statement
+                                               |  *declare_statement
+                                               |  *delete_statement
+                                               |  *disk_statement
+                                               |  *drop_database_statement
+                                               |  *drop_default_statement
+                                               |  *drop_index_statement
+                                               |  *drop_procedure_statement
+                                               |  *drop_rule_statement
+                                               |  *drop_table_statement
+                                               |  *drop_trigger_statement
+                                               |  *drop_view_statement
+                                               |  *dump_statement
+                                               |  *execute_statement
+                                               |  *fetch_statement
+                                               |  *goto_statement
+                                               |  *grant_statement
+                                               |  *insert_statement
+                                               |  *kill_statement
+                                               |  *label_statement
+                                               |  *load_statement
+                                               |  *online_database_statement
+                                               |  *open_statement
+                                               |  *prepare_transaction_statement
+                                               |  *print_statement
+                                               |  *raiserror_statement
+                                               |  *readtext_statement
+                                               |  *reconfigure_statement
+                                               |  *return_statement
+                                               |  *revoke_statement
+                                               |  *rollback_transaction_statement
+                                               |  *rollback_trigger_statement
+                                               |  *save_transaction_statement
+                                               |  *select_expr
+                                               |  *set_statement
+                                               |  *setuser_statement
+                                               |  *shutdown_statement
+                                               |  *truncate_statement
+                                               |  *update_statement
+                                               |  *update_statistics_statement
+                                               |  *use_statement
+                                               |  *waitfor_statement
+                                               |  *while_statement
+                                               |  *writetext_statement
            opt_any_or_all                      =  !(any | all)
            condition                           =  *condition_term | *condition or *condition_term
            condition_term                      =  *condition_factor | *condition_term and *condition_factor
            condition_factor                    =  *condition_element | not *condition_factor
            condition_element                   =  *column $'*=' *column
+                                               |  *column $'=*' *column
+                                               |  *expr $'=' *opt_any_or_all *expr
+                                               |  *expr $'>' *opt_any_or_all *expr
+                                               |  *expr $'<' *opt_any_or_all *expr
+                                               |  *expr $'>=' *opt_any_or_all *expr
+                                               |  *expr $'<=' *opt_any_or_all *expr
+                                               |  *expr $'<>' *opt_any_or_all *expr
+                                               |  *expr $'!=' *opt_any_or_all *expr
+                                               |  *expr $'!>' *opt_any_or_all *expr
+                                               |  *expr $'!<' *opt_any_or_all *expr
+                                               |  *expr in $'(' *expr_list $')'
+                                               |  *expr not in $'(' *expr_list $')'
+                                               |  *expr in $'(' *select_statement $')'
+                                               |  *expr not in $'(' *select_statement $')'
+                                               |  exists *expr
+                                               |  *expr between *expr and *expr
+                                               |  *expr not between *expr and *expr
+                                               |  *expr like *expr
+                                               |  *expr like *expr escape *expr
+                                               |  *expr not like *expr
+                                               |  *expr not like *expr escape *expr
+                                               |  *expr is null
+                                               |  *expr is not null
+                                               |  $'(' *condition $')'
            boolean_expr                        =  *boolean_expr_term | *boolean_expr or *boolean_expr_term
            boolean_expr_term                   =  *boolean_expr_factor | *boolean_expr_term and *boolean_expr_factor
            boolean_expr_factor                 =  *expr | not *boolean_expr_factor
            logical_expr                        =  *boolean_expr | *condition
            expr_list                           =  *expr | *expr_list $',' *expr
            expr                                =  *expr_expr
            expr_expr                           =  *expr_term
+                                               |  *expr_expr $'+' *expr_term
+                                               |  *expr_expr $'-' *expr_term
+                                               |  *expr_expr $'&' *expr_term
+                                               |  *expr_expr $'|' *expr_term
+                                               |  *expr_expr $'^' *expr_term
            expr_term                           =  *expr_factor
+                                               |  *expr_term $'*' *expr_factor
+                                               |  *expr_term $'/' *expr_factor
+                                               |  *expr_term $'%' *expr_factor
            expr_factor                         =  *expr_element
+                                               |  $'+' *expr_factor
+                                               |  $'-' *expr_factor
+                                               |  $'~' *expr_factor
            expr_element                        =  null
+                                               |  *string
+                                               |  *number
+                                               |  *number $'.' *number
+                                               |  $'$' *number
+                                               |  $'$' *number $'.' *number
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *column
+                                               |  *builtin_function
+                                               |  *aggregate_function
+                                               |  identity $'(' *number $')'
+                                               |  $'(' *select_statement $')'
+                                               |  $'(' *expr $')'
            builtin_function                    =  *ident $'(' $')'
+                                               |  *ident $'(' *expr_list $')'
+                                               |  convert $'(' *datatype $',' *expr $')'
+                                               |  convert $'(' *datatype $',' *expr $',' *expr $')'
            aggregate_function                  =  count $'(' $'*' $')'
+                                               |  min $'(' *expr $')'
+                                               |  max $'(' *expr $')'
+                                               |  avg $'(' !(all | distinct) *expr $')'
+                                               |  count $'(' !(all | distinct) *expr $')'
+                                               |  sum $'(' !(all | distinct) *expr $')'
            datatype                            =  *ident
+                                               |  double precision
+                                               |  *ident $'(' *number $')'
+                                               |  *ident varying $'(' *number $')'
+                                               |  national *ident $'(' *number $')'
+                                               |  national *ident varying $'(' *number $')'
+                                               |  *ident $'(' *number $',' *number $')'
            column_definitions                  =  *column_definition | *column_definitions $',' *column_definition
            column_definition                   =  *column_name
+                                                  *datatype
+                                                  !(default *expr)
+                                                  !%(
+                                                     identity
+                                                  |  !(constraint *constraint_name)
+                                                     (  null
+                                                     |  not null
+                                                     |  unique !(clustered | nonclustered) *constraint_options
+                                                     |  primary key !(clustered | nonclustered) *constraint_options
+                                                     |  references *table !($'(' *column_name $')')
+                                                     |  check $'(' *condition $')'
+                                                     )
+                                                  )
            constraint_definition               =  !(constraint *constraint_name)
+                                                  (  unique
+                                                     !(clustered | nonclustered)
+                                                     $'('
+                                                     *column_name_list
+                                                     $')'
+                                                     *constraint_options
+                                                  |  primary
+                                                     key
+                                                     !(clustered | nonclustered)
+                                                     $'('
+                                                     *column_name_list
+                                                     $')'
+                                                     *constraint_options
+                                                  |  foreign
+                                                     key
+                                                     $'('
+                                                     *column_name_list
+                                                     $')'
+                                                     references
+                                                     *table
+                                                     !($'(' *column_name_list $')')
+                                                  |  check $'(' *condition $')'
+                                                  )
            constraint_options                  =  !(with (fillfactor $'=' *x | max_rows_per_page $'=' *x))
+                                                  !(on *segment_name)
            index_access                        =  !($'(' index *index_name !(prefetch *size) !(lru | mru) $')')
            name_list                           =  *ident | *name_list $',' *ident
            permission_list                     =  *permission | *permission_list $',' *permission
            permission                          =  delete | exec | execute | insert | references | select | update
            command_list                        =  *command | *command_list $',' *command
            command                             =  create database
+                                               |  create default
+                                               |  create procedure
+                                               |  create rule
+                                               |  create table
+                                               |  create view
            alter_database_statement            =  alter
+                                                  database
+                                                  *database_name
+                                                  !(on *database_on_devices)
+                                                  !(log on *database_on_devices)
+                                                  !(with override)
+                                                  !(for load)
            database_on_devices                 =  (default | *database_device) !($'=' *size)
+                                               |  *database_on_devices $',' *database_device !($'=' *size)
            alter_table_statement               =  alter
+                                                  table
+                                                  *table
+                                                  (  add *column_definitions
+                                                  |  add *constraint_definition
+                                                  |  drop constraint *constraint_name
+                                                  |  partition *number
+                                                  |  replace *column_name default *expr
+                                                  |  unpartition
+                                                  )
            begin_statement                     =  begin *SQL_statements end
            begin_transaction_statement         =  begin (transaction | tran) !*transaction_name
            break_statement                     =  break
            checkpoint_statement                =  checkpoint
            close_statement                     =  close *cursor_name
            commit_transaction_statement        =  commit (transaction | tran | work) !*transaction_name
            continue_statement                  =  continue
            create_database_statement           =  create
+                                                  database
+                                                  *database_name
+                                                  !(on *database_on_devices)
+                                                  !(log on *database_on_devices)
+                                                  !(with override)
+                                                  !(for load)
            create_default_statement            =  create default *owner_object as *expr
            create_index_statement              =  create
+                                                  !unique
+                                                  !(clustered | nonclustered)
+                                                  index
+                                                  *index_name
+                                                  on
+                                                  *table
+                                                  $'('
+                                                  *column_name_list
+                                                  $')'
+                                                  !(with *create_index_options)
+                                                  !(on *segment_name)
            create_index_options                =  *create_index_option
+                                               |  *create_index_options $',' *create_index_option
            create_index_option                 =  *ident | fillfactor $'=' *expr | max_rows_per_page $'=' *expr
            create_procedure_statement          =  create
+                                                  (proc | procedure)
+                                                  *owner_object
+                                                  !($';' *number)
+                                                  !(*create_procedure_parameters
+                                               |  $'(' *create_procedure_parameters $')')
+                                                  !(with recompile)
+                                                  as
+                                                  *SQL_statements
            create_procedure_parameters         =  *create_procedure_parameter
+                                               |  *create_procedure_parameters $',' *create_procedure_parameter
            create_procedure_parameter          =  *parameter *datatype !($'=' *expr) !output
            create_rule_statement               =  create rule *owner_object as *condition
            create_table_statement              =  create
+                                                  table
+                                                  *table
+                                                  $'('
+                                                  *create_table_definitions
+                                                  $')'
+                                                  !(with max_rows_per_page $'=' *x)
+                                                  !(on *segment_name)
            create_table_definitions            =  *create_table_definition
+                                               |  *create_table_definitions $',' *create_table_definition
            create_table_definition             =  *column_definition | *constraint_definition
            create_trigger_statement            =  create
+                                                  trigger
+                                                  *owner_object
+                                                  on
+                                                  *owner_object
+                                                  for
+                                                  *create_trigger_for_options
+                                                  as
+                                                  *create_trigger_body
            create_trigger_for_options          =  *create_trigger_for_option
+                                               |  *create_trigger_for_options $',' *create_trigger_for_option
            create_trigger_for_option           =  insert | update | delete
            create_trigger_body                 =  *SQL_statement
+                                               |  *create_trigger_if_update_clause *SQL_statement
+                                               |  *create_trigger_body *SQL_statement
+                                               |  *create_trigger_body *create_trigger_if_update_clause *SQL_statement
            create_trigger_if_update_clause     =  if
+                                                  update
+                                                  $'('
+                                                  *column_name
+                                                  $')'
+                                                  !%((and | or) update $'(' *column_name $')')
            create_view_statement               =  create
+                                                  view
+                                                  *view
+                                                  !($'(' *column_name_list $')')
+                                                  as
+                                                  *select_statement
+                                                  !(with check option)
            dbcc_statement                      =  dbcc *ident | dbcc *ident $'(' *expr_list $')'
            deallocate_cursor_statement         =  deallocate cursor *cursor_name
            declare_statement                   =  declare *declare_local_variables
            declare_local_variables             =  *declare_local_variable
+                                               |  *declare_local_variables $',' *declare_local_variable
            declare_local_variable              =  *local_variable *datatype
            declare_cursor_statement            =  declare *cursor_name cursor for *select_statement
            delete_statement                    =  delete
+                                                  !from
+                                                  *table_or_view
+                                                  !(from *delete_from_clause
+                                               |  from *delete_from_clause where *condition
+                                               |  where *condition
+                                               |  where current of *cursor_name)
            delete_from_clause                  =  *delete_from_entity | *delete_from_clause $',' *delete_from_entity
            delete_from_entity                  =  *table_or_view !*ident *index_access
            disk_statement                      =  disk *ident !*disk_options
            disk_options                        =  *disk_option | *disk_options $',' *disk_option
            disk_option                         =  *ident | *ident $'=' *expr
            drop_database_statement             =  drop database *database_name_list
            drop_default_statement              =  drop default *owner_object_list
            drop_index_statement                =  drop index *table_index_name_list
            table_index_name_list               =  *table_index_name | *table_index_name_list $',' *table_index_name
            table_index_name                    =  *table_name $'.' *index_name
            drop_procedure_statement            =  drop (proc | procedure) *owner_object_list
            drop_rule_statement                 =  drop rule *owner_object_list
            drop_table_statement                =  drop table *owner_object_list
            drop_trigger_statement              =  drop trigger *owner_object_list
            drop_view_statement                 =  drop view *owner_object_list
            dump_statement                      =  dump
+                                                  (database | tran | transaction)
+                                                  *database_name
+                                                  !(to *database_device)
+                                                  !(at *server_name)
+                                                  !*dump_options
+                                                  !%(stripe on *database_device !(at *server_name) !*dump_options)
+                                                  !(with *dump_with_options)
            dump_options                        =  *dump_option | *dump_options $',' *dump_option
            dump_option                         =  *ident $'=' *expr
            dump_with_options                   =  *dump_with_option | *dump_with_options $',' *dump_with_option
            dump_with_option                    =  *ident | *ident $'=' *expr
            execute_statement                   =  (exec | execute) *execute_command
            execute_command                     =  !(*return_status $'=')
+                                                  *server_procedure
+                                                  !($';' *number)
+                                                  !*execute_parameters
+                                                  !(with recompile)
            execute_parameters                  =  *execute_parameter | *execute_parameters $',' *execute_parameter
            execute_parameter                   =  *value
+                                               |  *parameter $'=' *value
+                                               |  *local_variable !(out | output)
+                                               |  *parameter $'=' *local_variable !(out | output)
            value                               =  common
+                                               |  foreign
+                                               |  mru
+                                               |  null
+                                               |  prefetch
+                                               |  primary
+                                               |  *ident
+                                               |  *string
+                                               |  *number
            fetch_statement                     =  fetch *cursor_name !(into *fetch_target_list)
            fetch_target_list                   =  *fetch_target | *fetch_target_list $',' *fetch_target
            fetch_target                        =  *local_variable
            goto_statement                      =  goto *ident
            grant_statement                     =  grant
+                                                  (all !privileges | *permission_list)
+                                                  on
+                                                  *owner_object
+                                                  !($'(' *column_name_list $')')
+                                                  to
+                                                  (public | *name_list)
+                                                  !(with grant option)
+                                               |  grant
+                                                  (all !privileges | *command_list)
+                                                  to
+                                                  (null | public | *name_list)
            insert_statement                    =  insert
+                                                  !into
+                                                  *table_or_view
+                                                  !($'(' *column_name_list $')')
+                                                  (values $'(' *expr_list $')' | *select_expr)
            kill_statement                      =  kill *number
            label_statement                     =  *label
            load_statement                      =  load
+                                                  (database | tran | transaction)
+                                                  *database_name
+                                                  (from | to)
+                                                  *database_device
+                                                  !(at *server_name)
+                                                  !*load_options
+                                                  !%(stripe on *database_device !(at *server_name) !*load_options)
+                                                  !(with !*load_options)
            load_options                        =  *load_option | *load_options $',' *load_option
            load_option                         =  *ident $'=' *expr
            online_database_statement           =  online database *database_name
            open_statement                      =  open *cursor_name
            prepare_transaction_statement       =  prepare (tran | transaction)
            print_statement                     =  print *print_arguments
            print_arguments                     =  *print_argument | *print_arguments $',' *print_argument
            print_argument                      =  *number | *string | *local_variable | *global_variable
            raiserror_statement                 =  raiserror
+                                                  *error_number
+                                                  !(!$',' *raiserror_arguments)
+                                                  !*raiserror_extended_values
            raiserror_arguments                 =  *raiserror_argument | *raiserror_arguments $',' *raiserror_argument
            raiserror_argument                  =  *string | *local_variable
            raiserror_extended_values           =  *raiserror_extended_value
+                                               |  *raiserror_extended_values $',' *raiserror_extended_value
            raiserror_extended_value            =  *extended_value $'=' *extended_value
            readtext_statement                  =  readtext
+                                                  *column
+                                                  (*local_variable | *number)
+                                                  *number
+                                                  *number
+                                                  !holdlock
+                                                  !(using *ident)
+                                                  !(at isolation (read uncommitted | read committed | serializable))
            reconfigure_statement               =  reconfigure !(with override)
            return_statement                    =  return | return *expr
            revoke_statement                    =  revoke
+                                                  (  (*all_privileges | *permission_list)
+                                                     on
+                                                     *owner_object
+                                                     !($'(' *column_name_list $')')
+                                                     (from | to)
+                                                     (public | *name_list)
+                                                     !cascade
+                                                  |  grant
+                                                     option
+                                                     for
+                                                     (*all_privileges | *permission_list)
+                                                     on
+                                                     *owner_object
+                                                     !($'(' *column_name_list $')')
+                                                     (from | to)
+                                                     (public | *name_list)
+                                                     !cascade
+                                                  |  (*all_privileges | *command_list)
+                                                     (from | to)
+                                                     (public | *name_list)
+                                                  )
            all_privileges                      =  all !privileges
            rollback_transaction_statement      =  rollback (transaction | tran | work) !*transaction_name
            rollback_trigger_statement          =  rollback trigger !(with *raiserror_statement)
            save_transaction_statement          =  save (transaction | tran) *savepoint_name
            select_expr                         =  *select_statement
+                                               |  *select_expr union *select_expr_term
+                                               |  *select_expr union all *select_expr_term
            select_expr_term                    =  *select_statement | $'(' *select_expr $')'
            select_statement                    =  select
+                                                  *select_all_or_distinct
+                                                  ($'*' | *select_item_list)
+                                                  !(into *table)
+                                                  !(from *select_references)
+                                                  !(where *condition)
+                                                  !(group by !all *expr_list)
+                                                  !(having *condition)
+                                                  !(order by *select_order_by_expr_list)
+                                                  !(compute *select_compute_list !(by *column_name_list))
+                                                  !(*select_for_read_only
+                                               |  *select_for_read_only *select_at_isolation
+                                               |  *select_for_read_only *select_for_browse
+                                               |  *select_for_read_only *select_at_isolation *select_for_browse
+                                               |  *select_for_update
+                                               |  *select_for_update *select_at_isolation
+                                               |  *select_for_update *select_for_browse
+                                               |  *select_for_update *select_at_isolation *select_for_browse
+                                               |  *select_at_isolation
+                                               |  *select_at_isolation *select_for_browse
+                                               |  *select_for_browse)
            select_order_by_expr_list           =  *select_order_by_expr
+                                               |  *select_order_by_expr_list $',' *select_order_by_expr
            select_order_by_expr                =  *expr !(asc | desc)
            select_compute_list                 =  *select_compute | *select_compute_list $',' *select_compute
            select_compute                      =  *row_aggregate $'(' *column_name $')'
            select_all_or_distinct              =  !(all | distinct)
            select_item_list                    =  *select_item | *select_item_list $',' *select_item
            select_item                         =  syb_identity
+                                               |  *ident $'.' $'*'
+                                               |  *ident $'.' syb_identity
+                                               |  *ident $'.' *ident $'.' $'*'
+                                               |  *alias $'=' *expr
+                                               |  *local_variable $'=' *expr
+                                               |  *expr
+                                               |  *expr *alias
+                                               |  *expr as *alias
            select_references                   =  *select_reference | *select_references $',' *select_reference
            select_reference                    =  *table_or_view
+                                                  !*ident
+                                                  *index_access
+                                                  !(holdlock | noholdlock)
+                                                  !shared
            select_for_read_only                =  for read only
            select_for_update                   =  for update !(of *column_name_list)
            select_for_browse                   =  for browse
            select_at_isolation                 =  at isolation (read uncommitted | read committed | serializable)
            set_statement                       =  set *ident *set_on_or_off
+                                               |  set *ident *ident
+                                               |  set *ident *number
+                                               |  set *ident *string
+                                               |  set *ident *string *set_on_or_off
+                                               |  set *ident arith_overflow *set_on_or_off
+                                               |  set *ident numeric_truncation *set_on_or_off
+                                               |  set char_convert (off | on !(with *ident) | *ident !(with *ident))
+                                               |  set cursor rows *number for *cursor_name
+                                               |  set table count *number
+                                               |  set transaction isolation level *number
            set_on_or_off                       =  on | off
            setuser_statement                   =  setuser | setuser *string
            shutdown_statement                  =  shutdown !*server_name !(with (wait | nowait))
            truncate_statement                  =  truncate table *table
            update_statement                    =  update
+                                                  *table_or_view
+                                                  set
+                                                  *column
+                                                  $'='
+                                                  *expr
+                                                  !%($',' *column_name $'=' *expr)
+                                                  !(from *update_from_clause
+                                               |  from *update_from_clause where *condition
+                                               |  where *condition
+                                               |  where current of *cursor_name)
            update_from_clause                  =  *update_from_entity | *update_from_clause $',' *update_from_entity
            update_from_entity                  =  *table_or_view !*ident *index_access
            update_statistics_statement         =  update statistics *table !*index_name
            use_statement                       =  use *database_name
            waitfor_statement                   =  waitfor
+                                                  (delay *time | time *time | errorexit | processexit | mirrorexit)
            while_statement                     =  while *logical_expr *SQL_command_statement
            writetext_statement                 =  writetext *column *expr !(with log) *string
 target =
+   *ebnf

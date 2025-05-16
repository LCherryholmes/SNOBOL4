            x1_partitioned_table_clause         =  $'('
+                                                  (  PARTITION !(*partition !%*nonempty_segment_attributes_clause)
+                                                  ) % $','
+                                                  $')'

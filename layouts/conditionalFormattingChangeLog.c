Template for logging changes:

[name #] Change description and purpose:
Paste conditional formula or value here.  
	
NOTE: If change is to an item already in this log, then write over it 
so that everyone can see the red and green change indictor in GitHub.
Also, replaceing existing items in this log insures that the log
is current with the version of FileMaker file in your repository.
	
Log Conditional Formatting Changes Below Here (Leave the description text above.)

[Learn TagMenus 108] fix conditional formatting so it only shows when reference records are referenced:  
ValueCount ( $$ref  ) - Length ( Filter ( $$ref ; "L" )  )  ≠ Length ( Filter ( $$ref ; "L" )  ) - Length ( Filter ( $$ref ; "L" )  )
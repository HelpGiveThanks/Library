January 10, 2018 15:01:46 Library.fmp12 - tagLoop -1-
dataCleanUpScripts: tagLoop
#
#Use this script to change some information in all
#records currently found. Useful for when you make
#an error covering many records to correct the error.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “tableTag” (tagTable) ]
Show All Records
Go to Record/Request/Page
[ First ]
Loop
#
If [ tagTable::match = "health" ]
Set Field [ tagTable::match; "copyright" ]
End If
#
If [ tagTable::match = "organ" ]
Set Field [ tagTable::match; "publication" ]
End If
#
If [ tagTable::match = "copyist" ]
Set Field [ tagTable::match; "publisher" ]
End If
#
If [ tagTable::match = "sample" ]
Set Field [ tagTable::match; "brainstorm" ]
End If
#
If [ tagTable::match = "focus" ]
Set Field [ tagTable::match; "testSection" ]
End If
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]

January 21, 2018 11:09:43 Library.fmp12 - CHUNK_insertPageNumbers -1-
test: report: print: CHUNK_insertPageNumbers
Set Variable [ $$theme; Value:reportSubsection::ksubsectionGroup ]
If [ $$themepage = 1 ]
Set Field [ report::pagenumberTheme; TEMP::pageNumber ]
Set Variable [ $$themepage; Value:2 ]
Refresh Window
Else If [ $$themepage = 2 ]
Set Field [ report::pagenumberItem; TEMP::pageNumber ]
Go to Record/Request/Page
[ Next ]
Set Field [ report::CurrentRecord; Get ( RecordID ) ]
End If
If [ $$theme ≠ reportSubsection::ksubsectionGroup ]
Set Variable [ $$themepage; Value:1 ]
Set Field [ report::CurrentRecord; Get ( RecordID ) ]
Refresh Window
End If

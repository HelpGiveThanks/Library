testScreens: testReport: Print: CHUNK_insertPageNumbers
Set Variable [ $$theme; Value:reportItem::ktestGroup ]
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
If [ $$theme ≠ reportItem::ktestGroup ]
Set Variable [ $$themepage; Value:1 ]
Set Field [ report::CurrentRecord; Get ( RecordID ) ]
Refresh Window
End If
January 7, 平成26 14:47:36 Imagination Quality Management.fp7 - CHUNK_insertPageNumbers -1-

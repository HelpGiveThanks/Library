reference(citation): extractCreateDateFromReferenceRecords
Loop
Set Variable [ $number; Value:reference::_Lreference ]
If [ Middle ( $number ; 5 ; 2 ) ≠ 20 ]
Set Variable [ $number; Value:0 & reference::_Lreference ]
End If
Set Field [ reference::createDate; Left ( $number ; 2 ) & "/" & Middle ( $number ; 3 ; 2 ) & "/" & Middle ( $number ; 5 ; 4 ) & " " & Middle ( $number ; 9 ; 2 ) & ":" & Middle ( $number ; 11 ; 2 ) & ":" & Middle ( $number ; 13 ; 2 ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
January 7, 平成26 17:43:35 Imagination Quality Management.fp7 - extractCreateDateFromReferenceRecords -1-

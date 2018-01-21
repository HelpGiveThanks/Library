January 21, 2018 12:11:28 Library.fmp12 - extractCreateDateFromReferenceRecords -1-
reference: extractCreateDateFromReferenceRecords
Loop
Set Variable [ $number; Value:reference::_Lreference ]
If [ Middle ( $number ; 5 ; 2 ) ≠ 20 ]
Set Variable [ $number; Value:0 & reference::_Lreference ]
End If
Set Field [ reference::createDate; Left ( $number ; 2 ) & "/" & Middle ( $number ; 3 ; 2 ) & "/" & Middle ( $number ; 5 ; 4 ) & " " &
Middle ( $number ; 9 ; 2 ) & ":" & Middle ( $number ; 11 ; 2 ) & ":" & Middle ( $number ; 13 ; 2 ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop

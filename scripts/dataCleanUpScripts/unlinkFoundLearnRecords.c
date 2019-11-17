December 10, 2018 12:28:57 Library.fmp12 - -1-
unlinkFoundLearnRecords
dataCleanUpScripts: unlinkFoundLearnRecords
Set Variable [ $$stoploadCitation; Value:1 ]
Loop
Set Variable [ $count; Value:ValueCount ( testlearn::kcreference ) ]
Loop
If [ Filter ( GetValue ( testlearn::kcreference ; $count ) ; "L" ) = "L" ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( testlearn::kcreference) ≠ ValueCount ( Substitute ( testlearn::kcreference ; GetValue ( testlearn::
kcreference ; $count ) & "¶" ; "" ) ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ) & "¶" ; "" ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ); "" )
) ]
End If
Set Variable [ $count; Value:$count - 1 ]
Exit Loop If [ $count = 0 ]
End Loop
Go to Record/Request/Page
[ Next ]
End Loop
Set Variable [ $$stoploadCitation ]

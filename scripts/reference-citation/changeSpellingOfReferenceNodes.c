reference(citation): changeSpellingOfReferenceNodes
Set Variable [ $key; Value:reference::referenceNodes ]
Set Variable [ $keyOLD; Value:reference::referenceNodesOLD ]
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#
If [ $keyOLD & "¶" = FilterValues ( $keychain ; $keyOLD & "¶" ) and $key = "" ]
Set Field [ reference::kcopyrightHolder; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
//If ( ValueCount ( $keyChain ) ≠ ValueCount ( Substitute ( $keyChain ; $key & "¶" ; "" ) ) ;
Substitute ( $keyChain ; $keyOLD & "¶" ; "" ) //;
//Substitute ( $keyChain ; $key ; "" )
//) ]
Else If [ $keyOLD & "¶" = FilterValues ( $keychain ; $keyOLD & "¶" ) ]
Set Field [ reference::kcopyrightHolder; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
//If ( ValueCount ( $keyChain ) ≠ ValueCount ( Substitute ( $keyChain ; $key & "¶" ; "" ) ) ;
Substitute ( $keyChain ; $keyOLD & "¶" ; $key & "¶" ) //;
//Substitute ( $keyChain ; $key ; "" )
//) ]
End If
Set Field [ reference::referenceNodesOLD; $key ]
January 7, 平成26 17:40:18 Imagination Quality Management.fp7 - changeSpellingOfReferenceNodes -1-

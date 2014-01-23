reference(citation): CopyrightHolderDeleteEditor
#
#Get the keys currently unlocking who is a
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#If user has deleted all editors then start process
#of removing editor copyright key if it is on the keychain.
Go to Field [ ]
If [ $$citationMatch = "editors" and reference::compilationEditors = "" ]
Set Variable [ $key; Value:"editors857398f839" ]
End If
#
#If user has deleted all government authors then start process
#of removing governmentAuthor copyright key if it is on the keychain.
Go to Field [ ]
If [ $$citationMatch = "governmentAuthor" and reference::governmentAuthor = "" ]
Set Variable [ $key; Value:"governmentAuthor6767767676" ]
End If
#
#Remove key from keychain
If [ $key & "¶" = FilterValues ( $keychain ; $key & "¶" ) ]
Set Field [ reference::kcopyrightHolder; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
//If ( ValueCount ( $keyChain ) ≠ ValueCount ( Substitute ( $keyChain ; $key & "¶" ; "" ) ) ;
Substitute ( $keyChain ; $key & "¶" ; "" ) //;
//Substitute ( $keyChain ; $key ; "" )
//) ]
Exit Script [ ]
End If
#
January 7, 平成26 17:53:37 Imagination Quality Management.fp7 - CopyrightHolderDeleteEditor -1-

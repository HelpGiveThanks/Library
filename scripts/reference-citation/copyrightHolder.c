reference(citation): CopyrightHolder
#
#If user is on copyright holder ﬁeld perform script.
If [ $$citationMatch = "node" or
$$citationMatch = "copyist" or
$$citationMatch = "organ" or
$$citationMatch = "referenceNodes" or
$$citationMatch = "editors" or
$$citationMatch = "governmentAuthor" ]
#
#Get the keys currently unlocking who is a
#copyright holder.
Set Variable [ $keyChain; Value:reference::kcopyrightHolder ]
#
#Figure out what ﬁeld the user wants to designate
#as a copyright holder for this citation.
If [ $$citationMatch = "node" ]
Set Variable [ $key; Value:"node738fds8ef" ]
#
#If the ﬁeld is blank exit the script.
If [ reference::knodePrimary = "" and reference::knodeOther = "" ]
Show Custom Dialog [ Message: "Select a node ﬁrst and then click on this button. A yellow line will appear above the copyright holder's name."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "copyist" ]
Set Variable [ $key; Value:reference::kcopyist ]
#
#If the ﬁeld is blank exit the script.
If [ reference::kcopyist = "" ]
Show Custom Dialog [ Message: "Select a copyist ﬁrst and then click on this button. A yellow line will appear above the copyright holder's name."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "organ" ]
Set Variable [ $key; Value:reference::korgan ]
#
#If the ﬁeld is blank exit the script.
If [ reference::korgan = "" ]
Show Custom Dialog [ Message: "Select an organ ﬁrst and then click on this button. A yellow line will appear above the copyright holder's name."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "editors" ]
Go to Field [ ]
Set Variable [ $key; Value:"editors857398f839" ]
#
#If the ﬁeld is blank exit the script.
If [ reference::compilationEditors = "" ]
Show Custom Dialog [ Message: "Type in one or more editors' names ﬁrst and then click on this button. A yellow line will appear above the copyright holders' names."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "governmentAuthor" ]
Go to Field [ ]
Set Variable [ $key; Value:"governmentAuthor6767767676" ]
#
#If the ﬁeld is blank exit the script.
If [ reference::governmentAuthor = "" ]
Show Custom Dialog [ Message: "Type in gov't or corp. author name ﬁrst and then click on this button. A yellow line will appear above the copyright holders' names."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Else If [ $$citationMatch = "referenceNodes" ]
Go to Field [ ]
Set Variable [ $key; Value:reference::referenceNodes ]
#
#If the ﬁeld is blank exit the script.
If [ reference::referenceNodes = "" ]
Show Custom Dialog [ Message: "Type in one or more nodes ﬁrst and then click on this button. A yellow line will appear above the copyright holder's name."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If reference nodes are already designated as copyright
#holders, and user clicks in this ﬁeld and changes
#the spelling and then clicks the copyright holder
#button to indicate that the user does not want these
#to be copyright holders, remove them
#from the copyright holder keychain. In this case
#the text of their names is the key.
Set Variable [ $keyOLD; Value:reference::referenceNodesOLD ]
If [ $keyOLD & "¶" = FilterValues ( $keychain ; $keyOLD & "¶" ) ]
Set Field [ reference::kcopyrightHolder; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
//If ( ValueCount ( $keyChain ) ≠ ValueCount ( Substitute ( $keyChain ; $key & "¶" ; "" ) ) ;
Substitute ( $keyChain ; $keyOLD & "¶" ; "" ) //;
//Substitute ( $keyChain ; $key ; "" )
//) ]
Exit Script [ ]
End If
#
#Because citation nodes use the text in the ﬁeld
#as the key, the user needs to be exited from that
#text box so they can see the highlight appear
#when the copyright owner button is clicked.
Go to Field [ ]
End If
#
#Remove key from keychain if it is on
#the copyright holder keychain.
If [ $key & "¶" = FilterValues ( $keychain ; $key & "¶" ) ]
Set Field [ reference::kcopyrightHolder; //last item in list has no paragraph mark, so a valuecount test needs to be done and if item is not removed, then the removal calc without the paragraph mark is used
//If ( ValueCount ( $keyChain ) ≠ ValueCount ( Substitute ( $keyChain ; $key & "¶" ; "" ) ) ;
Substitute ( $keyChain ; $key & "¶" ; "" ) //;
//Substitute ( $keyChain ; $key ; "" )
//) ]
Exit Script [ ]
End If
#
#Add key to keychain if it is currenlty not on the
#the copyright holder keychain.
Set Field [ reference::kcopyrightHolder; $key & "¶" & $keyChain ]
#
Exit Script [ ]
End If
#
#If no copyright holder ﬁeld is selected ...
Show Custom Dialog [ Message: "Click into the ﬁeld with the copyright holder's name and then click on this button. A yellow line will appear above the copyright holder's name."; Buttons: “OK” ]
January 7, 平成26 17:53:06 Imagination Quality Management.fp7 - CopyrightHolder -1-

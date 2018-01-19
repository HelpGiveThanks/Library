January 18, 2018 14:40:27 Library.fmp12 - removeCopyrightType -1-
reference: removeCopyrightType
#
#
Set Variable [ $fieldName; Value:Get ( ActiveFieldName ) ]
#
#Remove author copyright holder if there are
#no authors.
If [ $fieldName = "referenceNodes" and reference::knodeOther = "" and reference::knodePrimary = "" and reference::referenceNodes =
"" ]
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "1" ) = 1 ]
Show Custom Dialog [ Message: "Author is currently checked in the copyright section for this reference as a copyright
holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "1" ; "" ) ]
End If
End If
End If
#
#Remove government author copyright holder if
#there isn't a government author.
If [ $fieldName = "governmentAuthor" and reference::governmentAuthor = "" ]
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "2" ) = 2 ]
Show Custom Dialog [ Message: "Government author is currently checked in the copyright section for this reference as a
copyright holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "2" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "2" ; "" ) ]
End If
End If
End If
#
#Remove editor copyright holder if there is not
#an editor.
If [ $fieldName = "compilationEditors" and reference::compilationEditors = "" ]
#Perform removal for items with and without a
#paragraph mark, as the last item in checklist
#has no paragraph mark after it.
If [ Filter ( reference::kcopyrightHolder ; "3" ) = 3 ]
Show Custom Dialog [ Message: "Editor is currently checked in the copyright section for this reference as a copyright
holder. Remove this check?"; Default Button: “No”, Commit: “Yes”; Button 2: “Yes”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "3" & "¶" ; "" ) ]
Set Field [ reference::kcopyrightHolder; Substitute ( reference::kcopyrightHolder ; "3" ; "" ) ]
End If
End If
End If

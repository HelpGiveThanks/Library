tagMenu: menuReferenceNodesOrEditors
#
#Set citationLock to color menu button with inUse color.
If [ Get ( ActiveFieldName ) = "referenceNodes" ]
Set Variable [ $$citationMatch; Value:"referenceNodes" ]
Else If [ Get ( ActiveFieldName ) = "compilationEditors" ]
Set Variable [ $$citationMatch; Value:"editors" ]
Else If [ Get ( ActiveFieldName ) = "governmentAuthor" ]
Set Variable [ $$citationMatch; Value:"governmentAuthor" ]
End If
#
Refresh Window
Perform Script [ “clearCitationMatch” ]
January 7, 平成26 16:18:32 Imagination Quality Management.fp7 - menuReferenceNodesOrEditors -1-

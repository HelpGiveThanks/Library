January 19, 2018 14:42:58 Library.fmp12 - CHUNKaddReferenceNodeAndKeywordTagIDs -1-
tagMenu: CHUNKaddReferenceNodeAndKeywordTagIDs
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Stop load tag record script to speed up this script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#Leave field so user can see
#conditional formatting.
Go to Field [ ]
#
#Get node and keyword tags linked to this
#main record.
If [ Get ( LayoutTableName ) = "reference" ]
Set Variable [ $nodePrimary; Value:reference::knodePrimary ]
Set Variable [ $nodeOther; Value:reference::knodeOther ]
Set Variable [ $keywordPrimary; Value:reference::kkeywordPrimary ]
Set Variable [ $keywordOther; Value:reference::kkeywordOther ]
Else If [ Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $nodePrimary; Value:testlearn::kNodePrimary ]
Set Variable [ $nodeOther; Value:testlearn::kNodeOther ]
Set Variable [ $keywordPrimary; Value:testlearn::kKeywordPrimary ]
Set Variable [ $keywordOther; Value:testlearn::kcKeywordOther ]
Else If [ Get ( LayoutTableName ) = "tagMenus" ]
Set Variable [ $nodePrimary; Value:TEMP::kdefaultNodePrimary ]
Set Variable [ $nodeOther; Value:TEMP::kdefaultNodeOther ]
Else If [ Get ( LayoutTableName ) = "tempSetup" ]
Set Variable [ $nodePrimary; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $nodeOther; Value:tempSetup::kdefaultNodeOther ]
End If
#
#Perform the rest of the script in a new window so
#users place is not lost in current window.
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “ltagNK1” (tagMenus) ]
#
#PRIMARY NODE
#Find primary node if there is one.
If [ $nodePrimary ≠ "" ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Perform Find [ ]
End If
#
#OTHER NODES
#Find other nodes if there are any.
If [ $nodeOther ≠ "" ]
#
#Determine how many keys there are to find for
#on the other nodes' keychain.
Set Variable [ $numberOfNodes; Value:ValueCount ( $nodeOther ) ]
#
#Loop thru each node record, with every key
#in the keychain.
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfNodes = 0 ]
#
#Find node.
Set Variable [ $$stopLoadCitation ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $nodeOther ; $numberOfNodes ) ]
Perform Find [ ]
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
End If
#
#
#
#
#PRIMARY KEYWORD
#Find all keywords assigned if there are any.
If [ $keywordPrimary ≠ "" ]
#Find in a new window so user's place is not lost
#on Tag Menus window.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $keywordPrimary ]
Perform Find [ ]
#
End If
#
#OTHER KEYWORDS
#Find all keywords assigned if there are any.
If [ $keywordOther ≠ "" ]
#
#Determine how many keys there are to find for
#on the other keywords' keychain.
Set Variable [ $numberOfKeywords; Value:ValueCount ( $keywordOther ) ]
#
#Loop thru each keyword record, with every key
#in the keychain.
Loop
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeywords = 0 ]
#
#Find keyword.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $keywordOther ; $numberOfKeywords ) ]
Perform Find [ ]
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeywords; Value:$numberOfKeywords - 1 ]
End Loop
End If
#
#Turn top load tag record script back on.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadCitation ]
#
Set Variable [ $$mainKeychain ]
Close Window [ Current Window ]
#

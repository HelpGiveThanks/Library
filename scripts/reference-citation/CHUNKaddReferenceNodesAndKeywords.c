reference(citation): CHUNKaddReferenceNodesAndKeywords
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Add current section key to reference record's
#section keychain if it is not on it already.
If [ TEMP::ksection & "¶" ≠ FilterValues ( reference::kcsection ; TEMP::ksection & "¶" ) and Get ( LayoutTableName ) = "reference" ]
Set Variable [ $sectionKeychain; Value:reference::kcsection ]
Set Field [ reference::kcsection; TEMP::ksection & ¶ & $sectionKeychain ]
End If
#
#Add current section key to learn record's
#section keychain if it is not on it already.
If [ TEMP::ksection & "¶" ≠ FilterValues ( testlearn::kcsection ; TEMP::ksection & "¶" ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $sectionKeychain; Value:testlearn::kcsection ]
Set Field [ testlearn::kcsection; TEMP::ksection & ¶ & $sectionKeychain ]
End If
#
// #Check main checkbox if record is not already
// #a main record. This is because when going to
// #edit cite or reference records, only main records
// #are shown by default.
// If [ "main" ≠ FilterValues ( reference::ﬁlterFind ; "main" ) and
Get ( LayoutTableName ) = "reference" and
$$add ≠ 1 ]
// Set Variable [ $ﬁlterFind; Value:reference::ﬁlterFind ]
// Set Field [ reference::ﬁlterFind; "main" & ¶ & $ﬁlterFind ]
// #
// Else If [ $$citationMatch ≠ FilterValues ( reference::ﬁlterFind ; $$citationMatch ) and
Get ( LayoutTableName ) = "reference" and
$$add = 1 ]
// Set Variable [ $ﬁlterFind; Value:reference::ﬁlterFind ]
// #
// If [ $$citationMatch ≠ "key" ]
// Set Field [ reference::ﬁlterFind; $$citationMatch & ¶ & $ﬁlterFind ]
// #
// Else If [ $$citationMatch = "key" ]
// Set Field [ reference::ﬁlterFind; "keyword" & ¶ & $ﬁlterFind ]
// End If
// #
// Else If [ "main" ≠ FilterValues ( testlearn::ﬁlterFind ; "main" ) and Get ( LayoutTableName ) = "testlearn" ]
// Set Variable [ $ﬁlterFind; Value:testlearn::ﬁlterFind ]
// Set Field [ testlearn::ﬁlterFind; "main" & ¶ & $ﬁlterFind ]
// End If
#
#Stop load tag record script to speed up this script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#Remove focus from ﬁeld so can see
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
Set Variable [ $$mainKeychain; Value:reference::kcsection ]
Else If [ Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $nodePrimary; Value:testlearn::kNodePrimary ]
Set Variable [ $nodeOther; Value:testlearn::kNodeOther ]
Set Variable [ $keywordPrimary; Value:testlearn::kKeywordPrimary ]
Set Variable [ $keywordOther; Value:testlearn::kcKeywordOther ]
Set Variable [ $$mainKeychain; Value:testlearn::kcsection ]
Else If [ Get ( LayoutTableName ) = "tagMenus" ]
Set Variable [ $nodePrimary; Value:TEMP::kdefaultNodePrimary ]
Set Variable [ $nodeOther; Value:TEMP::kdefaultNodeOther ]
Else If [ Get ( LayoutTableName ) = "tempSetup" ]
Set Variable [ $nodePrimary; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $nodeOther; Value:tempSetup::kdefaultNodeOther ]
Set Variable [ $$mainKeychain; Value:tempSetup::ksection ]
#Left this section in for setup, althought script never
#goes to setup section, so this is here just to note
#that I did think of this, but after testing determined
#the setup section is not neccessary.
End If
#
#Perform the rest of the script in a new window so
#users place is not lost in current window.
New Window [ ]
Go to Layout [ “ltagNK1” (tagMenus) ]
#
#PRIMARY NODE
#Find primary node if there is one.
If [ $nodePrimary ≠ "" ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Perform Find [ ]
#
#Add any section keys just added to the main record
#that are not in this tag's section group keychain.
If [ $nodePrimary = tagMenus::_Ltag ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain_addMode” ]
End If
End If
#
#OTHER NODES
#Find other nodes if there are any.
If [ $nodeOther ≠ "" ]
#
#Determine how many keys there are to ﬁnd for
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
January 7, 平成26 17:32:16 Imagination Quality Management.fp7 - CHUNKaddReferenceNodesAndKeywords -1-reference(citation): CHUNKaddReferenceNodesAndKeywords
Set Field [ tagMenus::_Ltag; GetValue ( $nodeOther ; $numberOfNodes ) ]
Perform Find [ ]
#
#Add any section keys just added to the main record
#that are not in this tag's section group keychain.
If [ GetValue ( $nodeOther ; $numberOfNodes ) = tagMenus::_Ltag ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain_addMode” ]
End If
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
#Find all keywords assigned if there are any.
If [ $keywordPrimary ≠ "" ]
#Find in a new window so user's place is not lost
#on Tag Menus window.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $keywordPrimary ]
Perform Find [ ]
#
#PRIMARY KEYWORD
#
#Add any section keys just added to the main record
#that are not in this tag's section group keychain.
If [ $keywordPrimary = tagMenus::_Ltag ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain_addMode” ]
End If
End If
#
#OTHER KEYWORDS
#Find all keywords assigned if there are any.
If [ $keywordOther ≠ "" ]
#
#Determine how many keys there are to ﬁnd for
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
#Add any section keys just added to the main record
#that are not in this tag's section group keychain.
If [ GetValue ( $keywordOther ; $numberOfKeywords ) = tagMenus::_Ltag ]
Perform Script [ “CHUNKaddMainSectionKeysToTagRecordKeychain_addMode” ]
End If
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
January 7, 平成26 17:32:16 Imagination Quality Management.fp7 - CHUNKaddReferenceNodesAndKeywords -2-

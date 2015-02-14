reference(citation): probablyNotInUse: addReferenceNodesAndKeywords Copy
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
#Check main checkbox if record is not already
#a main record. This is because when going to
#edit cite or reference records, only main records
#are shown by default.
If [ "main" & "¶" ≠ FilterValues ( reference::filterFind ; "main" & "¶" ) and
Get ( LayoutTableName ) = "reference" and
$$add ≠ 1 ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "main" & ¶ & $filterFind ]
#
Else If [ $$citationMatch & "¶" ≠ FilterValues ( reference::filterFind ; $$citationMatch & "¶" ) and
Get ( LayoutTableName ) = "reference" and
$$add = 1 ]
Set Variable [ $filterFind; Value:reference::filterFind ]
#
If [ $$citationMatch ≠ "key" ]
Set Field [ reference::filterFind; $$citationMatch & ¶ & $filterFind ]
#
Else If [ $$citationMatch = "key" ]
Set Field [ reference::filterFind; "keyword" & ¶ & $filterFind ]
End If
#
Else If [ "main" & "¶" ≠ FilterValues ( testlearn::filterFind ; "main" & "¶" ) and Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; "main" & ¶ & $filterFind ]
End If
#
#Stop load tag record script to speed up this script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#Remove focus from field so can see
#conditional formatting.
Go to Field [ ]
#
#Check if nodes and keywords linked to this
#reference record are in the current section
#or if the node is being used as a default.
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
End If
#
#Find all nodes assigned to this section.
#Find in a new window so user's place is not lost
#on Tag Menus window.
New Window [ ]
Set Variable [ $$stopLoadCitation ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#PRIMARY NODE
#Loop thru records to find primary node.
Go to Record/Request/Page
[ First ]
#
Loop
#
#If the key matches a lock or no locks exit the loop.
Exit Loop If [ $nodePrimary = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the primary key being tested, then add its
#group to the current section. ( Node groups are
# are assigned to sections, not individual nodes.
# So if the user wants one node to be assigned
# to a new section, its group and all nodes in
# its group must be assigned to the new section.
# The reason for this is because the display of
# nodes by catergory requires that each group
# have a unique name and that each node belong
# to a group. For the node to be the same node
# The group key it holds has to be the same as
# well, which means the group has to appear
# with the node, and with the group comes
# all the nodes assigned to it. )
If [ $nodePrimary ≠ tagMenus::_Ltag ]
#
#Find the node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
January 7, 平成26 18:02:09 Imagination Quality Management.fp7 - addReferenceNodesAndKeywords Copy -1-reference(citation): probablyNotInUse: addReferenceNodesAndKeywords Copy
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
End If
#
#OTHER NODES
#Determine how many keys there are to find for
#on the other nodes' keychain.
Set Variable [ $numberOfNodes; Value:ValueCount ( $nodeOther ) ]
#
#Loop thru each node record, with every key
#in the keychain.
Loop
Go to Record/Request/Page
[ First ]
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfNodes = 0 ]
Loop
#
#If the key matches a lock or no locks exit the loop.
#( The get value calculation works by going to the
# key in the list specified by the numberOfNodes
# variable, set before entering the loops.
# The system starts with the last key and with each
# loop moves to the next key up, until there are
# no more keys to check. )
Exit Loop If [ GetValue ( $nodeOther ; $numberOfNodes ) = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the other node key being tested, then add its
#group to the current section. ( Node groups are
# are assigned to sections, not individual nodes.
# So if the user wants one node to be assigned
# to a new section, its group and all nodes in
# its group must be assigned to the new section.
# The reason for this is because the display of
# nodes by catergory requires that each group
# have a unique name and that each node belong
# to a group. For the node to be the same node
# The group key it holds has to be the same as
# well, which means the group has to appear
# with the node, and with the group comes
# all the nodes assigned to it. )
If [ GetValue ( $nodeOther ; $numberOfNodes ) ≠ tagMenus::_Ltag ]
#
#Find the node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $nodeOther ; $numberOfNodes ) ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
#
#
#
#
#Find all keywords assigned to this section.
#Find in a new window so user's place is not lost
#on Tag Menus window.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "key" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#PRIMARY KEYWORD
#Loop thru records to find primary keyword.
Go to Record/Request/Page
[ First ]
#
Loop
#
#If the key matches a lock or no locks exit the loop.
Exit Loop If [ $keywordPrimary = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the primary keyword being tested, then add its
#group to the current section. ( Keyword groups are
# are assigned to sections, not individual keywords.
# So if the user wants one keyword to be assigned
# to a new section, its group and all keywords in
# its group must be assigned to the new section.
# The reason for this is because the display of
# keywords by group requires that each group
# have a unique name and that each keyword belong
# to a group. For the keyword to be the same
# keyword, the group key it holds has to be
# the same as well, which means the group
# has to appear with the keyword, and with
January 7, 平成26 18:02:09 Imagination Quality Management.fp7 - addReferenceNodesAndKeywords Copy -2-reference(citation): probablyNotInUse: addReferenceNodesAndKeywords Copy
# the group comes all the keywords assigned to it. )
If [ $keywordPrimary ≠ tagMenus::_Ltag ]
#
#Find the keyword to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $keywordPrimary ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all keywords, which now includes the
#keyword just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "key" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
End If
#
#OTHER KEYWORDS
#Determine how many keys there are to find for
#on the other keywords' keychain.
Set Variable [ $numberOfKeywords; Value:ValueCount ( $keywordOther ) ]
#
#Loop thru each keyword record, with every key
#in the keychain.
Loop
Go to Record/Request/Page
[ First ]
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeywords = 0 ]
Loop
#
#If the key matches a lock or no locks exit the loop.
#( The get value calculation works by going to the
# key in the list specified by the numberOfKeywords
# variable, set before entering the loops.
# The system starts with the last key and with each
# loop moves to the next key up, until there are
# no more keys to check. )
Exit Loop If [ GetValue ( $keywordOther ; $numberOfKeywords ) = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the primary keyword being tested, then add its
#group to the current section. ( Keyword groups are
# are assigned to sections, not individual keywords.
# So if the user wants one keyword to be assigned
# to a new section, its group and all keywords in
# its group must be assigned to the new section.
# The reason for this is because the display of
# keywords by group requires that each group
# have a unique name and that each keyword belong
# to a group. For the keyword to be the same
# keyword, the group key it holds has to be
# the same as well, which means the group
# has to appear with the keyword, and with
# the group comes all the keywords assigned to it. )
If [ GetValue ( $keywordOther ; $numberOfKeywords ) ≠ tagMenus::_Ltag ]
#
#Find the keyword to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $keywordOther ; $numberOfKeywords ) ]
Perform Find [ ]
#
#Next, add the current section key to this keyword's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all keywords, which now includes the
#keyword just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "key" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeywords; Value:$numberOfKeywords - 1 ]
End Loop
#
#Turn top load tag record script back on.
Set Variable [ $$stopLoadTagRecord ]
#
Close Window [ Current Window ]
#
January 7, 平成26 18:02:09 Imagination Quality Management.fp7 - addReferenceNodesAndKeywords Copy -3-

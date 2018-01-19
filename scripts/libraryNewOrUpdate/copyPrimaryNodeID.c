January 11, 2018 19:35:40 Library.fmp12 - copyPrimaryNodeID -1-
librarySetup:copyPrimaryNodeID
#
#
#Decided a user copy paste for Node ID was
#too risky. Will eventually create script to
#allow user to merge to nodes, after importing
#another libraries records.
#
#This was the old copy strategy...
#
// #Copy node ID.
// Copy [ tempSetup::CopyNodeIDforNewDatabase ]
[ Select ]
// Go to Field [ ]
// Show Custom Dialog [ Message: tempSetup::DEFAULTNodePrimaryName & "'s ID number " & tempSetup::kdefaultNodePrimary &
" has been copied."; Default Button: “OK”, Commit: “Yes” ]
#
#
#This is was the updated copy strategy...
#
// #Copy node ID.
// Set Field [ tagMenus::tag; tagMenus::_Ltag ]
// Copy [ tagMenus::tag ]
[ Select ]
// Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
// Go to Field [ ]
// Show Custom Dialog [ Message: "Node ID number — " & tagMenus::_Ltag & " — for node — " & tagMenus::tag & " — has been
successfully copied."; Default Button: “OK”, Commit: “No” ]

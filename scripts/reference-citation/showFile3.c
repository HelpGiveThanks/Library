January 18, 2018 15:43:09 Library.fmp12 - showTagLink3 -1-
reference: showTagLink3
#
#Capture needed link info.
Set Variable [ $$tagMenusRealCheckbox; Value:tagFileLocation3::kfileORkTestItemCreatorNode ]
Set Variable [ $$tagMenusFilePath; Value:tagFileLocation3::tag ]
Set Variable [ $$tagMenusFileName; Value:refTitle3::fileName ]
Set Variable [ $$tagMenusFileLocation; Value:refTitle3::kfileLocation ]
Set Variable [ $$tagMenusURL; Value:refTitle3::URL ]
Set Variable [ $$tagMenusISBN; Value:refTitle3::ISBN ]
Set Variable [ $$tagMenusISSN; Value:refTitle3::ISSN ]
Set Variable [ $$tagMenusDOI; Value:refTitle3::DOI ]
#
#Open link for user.
Perform Script [ “showReferencedFileFolderOrWebsite (update and name showFileInTagandLearnWindows)” ]
#
#Clear link variables.
Set Variable [ $$tagMenusRealCheckbox ]
Set Variable [ $$tagMenusFilePath ]
Set Variable [ $$tagMenusFileName ]
Set Variable [ $$tagMenusFileLocation ]
Set Variable [ $$tagMenusURL ]
Set Variable [ $$tagMenusISBN ]
Set Variable [ $$tagMenusISSN ]
Set Variable [ $$tagMenusDOI ]
#

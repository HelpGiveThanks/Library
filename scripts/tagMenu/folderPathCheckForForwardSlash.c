tagMenu: folderPathCheckForForwardSlash
If [ Right ( tagMenus::tag ; 1 ) ≠ "/" and $$citationMatch = "folderPath" ]
Show Custom Dialog [ Message: "All ﬁlepaths must end with forward slash /. Make sure you did not copy the ﬁle name along with the ﬁle path."; Buttons: “OK” ]
End If
January 7, 平成26 16:35:30 Imagination Quality Management.fp7 - folderPathCheckForForwardSlash -1-

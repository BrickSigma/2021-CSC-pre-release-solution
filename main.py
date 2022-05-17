Tutor_groups = ["7a","7b","7c","7d","7e","7f","8a","8b","8c","8d","8e","8f","9a","9b","9c","9d","9e","9f","10a","10b","10c","10d","10e","10f","11a","11b","11c","11d","11e","11f"]
Check = []
for count in range (30):

    CandidateNames = []
    CandidateList = []

    TutorName =  str(input("Please enter a tutor group name: "))
    while (TutorName not in Tutor_groups) or (TutorName in Check):
        if TutorName not in Tutor_groups:
            TutorName = str(input("Please enter a valid tutor group name: "))
        if TutorName in Check:
            TutorName = str(input("This tutor group has already voted. Please enter a different tutor group: "))
    Check.append (TutorName)
    
    StudentNumber = int(input("Please enter the number of students in tutor group: "))
    while (StudentNumber < 28) or (StudentNumber > 35):
        StudentNumber = int(input("Please enter the number of students between 28 and 35: "))

    CandidateNumber = int(input("Please enter the number of candidates running for the election: "))
    while (CandidateNumber > 4) or (CandidateNumber < 1):
        CandidateNumber = int(input("Only a maximum of 4 candidates can run, please re-enter the number of running candidates: "))

    for count_2 in range (CandidateNumber):
        CandidateNames.append (str(input("Please enter name of candidate: ")))
        name = CandidateNames[count_2]
        name = str(count_2+1) + ". " + name
        CandidateList.append (name)

    print ("")
    counter = 0
    number_of_ties = 1
    while number_of_ties > counter:
        Number_of_votes = [0,0,0,0]
        Number_of_abstaining = 0
        Vote_number = []
        count_3 = 0
        while count_3 < StudentNumber:

            print ("Please enter the last two digits of your vote number. For example, 05.")
            vote_ID = str(input("Enter the last two digits of your vote number here: "))
            vote_ID = TutorName + vote_ID
            print ("")
            if vote_ID not in Vote_number:
                print ("Your voting number is ", vote_ID)
                Vote_number.append (vote_ID)
                print ("")      
                voting_check = str(input("Are you voting? Type 'yes' if so, or 'no' to abstain: "))
                if (voting_check == "yes") or (voting_check == "Yes"):
                    for sub_count_3 in range (CandidateNumber):
                        print (CandidateList[sub_count_3])  
                    vote = str(input("Please enter the name of the candidate you would like to vote for from the list above: "))
                    while vote not in CandidateNames:
                        vote = str(input("Please enter the candidate name from the list above: "))
                    for sub_count_3 in range (CandidateNumber):
                        if vote == CandidateNames[sub_count_3]:
                            Number_of_votes[sub_count_3] = Number_of_votes[sub_count_3] + 1 
                elif (voting_check == "no") or (voting_check == "No"):
                    Number_of_abstaining = Number_of_abstaining + 1 
                count_3 = count_3 + 1
            elif vote_ID in Vote_number:
                print ("Sorry, you have already voted. You will not be allowed to vote again.")
            print ("")

        Highest = 0
        tie_list = []
        for count_4 in range (CandidateNumber):
            if Number_of_votes[count_4] > Highest:
                tie_list = []
                tie_list.append (count_4)
                Highest = Number_of_votes[count_4]
                Winners = CandidateNames[count_4]
                number_of_ties = 1
            elif Number_of_votes[count_4] == Highest:
                Winners = Winners + " and " + CandidateNames[count_4]
                number_of_ties = number_of_ties + 1
                tie_list.append (count_4)
                counter = 1

        print ("Tutor Group Name:")
        print ("=================")
        print (TutorName)
        print ("Number of votes for candidates:")
        print ("==============================")
        for count_5 in range (CandidateNumber):
            percentage = (Number_of_votes[count_5]/(StudentNumber - Number_of_abstaining)) *100
            print (CandidateList[count_5], "-", Number_of_votes[count_5], " - ", percentage, "%", " of students voted.")
        print ("")
        print ("Number of students who voted:")
        print ("=============================")
        print (StudentNumber - Number_of_abstaining)
        print ("Number of abstaining students:")
        print ("==============================")
        print (Number_of_abstaining)
        print ("")
        if number_of_ties > 1:
            print("There has been a tie between %s. The election will be run again." %Winners)
            name_writer = CandidateNames
            CandidateNames = []
            CandidateList = []
            for count in range (number_of_ties):
                CandidateNames.append (name_writer[tie_list[count]])
                CandidateList.append (str(count+1) + ". " + CandidateNames[count])
            CandidateNumber = number_of_ties
            print ("")
            print ("====================================================")
            print ("Re-election will now commence against tied candidates")
            print ("====================================================")
        elif number_of_ties == 1:
            print ("Winner of election:")
            print ("===================")
            print (Winners) 
            number_of_ties = 0
        print ("")
    print ("====================================================================")
    print ("")

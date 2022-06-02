def main():
    import sys

    args = sys.argv[1:]

    # check if user has provided input file
    if(len(args) != 1): 
        print("Incorrect usage. Please provide input file as an argument")
    else:
        import os
        import shutil

        input = args[0]
        inputExists = os.path.isfile(input)

        # check wether the input file exists or not
        if(inputExists): 
            folder = 'output'
            folderExists = os.path.isdir(folder)
            
            # check if the folder already exists
            if (folderExists):
                try:
                    shutil.rmtree(folder) # if it does, delete it
                except Exception as e:
                    print("Failed. Reason: %s" % e)

            # create the folder in either case
            os.mkdir(folder) 

            import cv2
            video = cv2.VideoCapture(input)
            count = 0

            while True:
                success,image = video.read() # get current frame
                if not success: # check if we didn't get any frame
                    break
                cv2.imwrite(os.path.join(folder, "frame{:d}.jpg".format(count)), image) # save the frame to the specified output path
                count += 1
                
            print ("{} frames have been outputted to '{}'.".format(count, folder))
        else:
            print ("%s does not exist." % input)


if __name__ == "__main__":
    main()
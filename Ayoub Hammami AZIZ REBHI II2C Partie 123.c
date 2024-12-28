import pyautogui
import time
import os
import random
from pyautogui import ImageNotFoundException
from pynput.keyboard import Controller, Key

keyboard = Controller()

# Paths to images and shortcuts
# Update ur own desktop Username
shortcut_path = r"C:\Users\Public\Desktop\League of Legends.lnk"
desktop_path = os.path.join(os.path.join(os.environ['USERPROFILE']), 'Desktop\Images')
play_image = os.path.join(desktop_path, 'play.png')
akshan_image = os.path.join(desktop_path, 'ak.png')
botQ_image = os.path.join(desktop_path, 'botQ.png')
noob_image = os.path.join(desktop_path, 'noob.png')
confirm_image = os.path.join(desktop_path, 'confirm.png')
find_match_image = os.path.join(desktop_path, 'find.png')
accept_image = os.path.join(desktop_path, 'accept.png')
gold_image = os.path.join(desktop_path, 'gold.png')
red_smite_image = os.path.join(desktop_path, 'red_smite.png')
spin_image = os.path.join(desktop_path, 'spin.png')
lock_image = os.path.join(desktop_path, 'lock.png')
done_image = os.path.join(desktop_path, 'done.png')
cont_image = os.path.join(desktop_path,'cont.png')
levelup_image = os.path.join(desktop_path,'levelup.png')
next_game_image= os.path.join(desktop_path,'next_game.png')
inQ_im = os.path.join(desktop_path,'inQ.png')
free_im = os.path.join(desktop_path,'akshan_icon.png')
daily_im = os.path.join(desktop_path,'daily.png')

# Initialize wandering flag
def detect_daily():
    try:
        daily_loc = pyautogui.locateCenterOnScreen(daily_im,confidence=0.8)
        if daily_loc:
            click_daily()
            print("Daily Champion reward clicked.")
            time.sleep(1)
            levelup()
    except Exception as e : 
            print("Error! occured")        

is_wandering = False
def click_daily():
    
    screen_width, screen_height = pyautogui.size()

    # Calculate the center
    center_x, center_y = screen_width // 2, screen_height // 2

    # Move the mouse pointer to the center
    pyautogui.moveTo(center_x, center_y)

    print(f"Mouse moved to the center: ({center_x}, {center_y})")

def start_league():
    if os.path.isfile(shortcut_path):
        try:
            os.startfile(shortcut_path)
            print("League of Legends client started.")
            time.sleep(32)  # Adjust the sleep time based on your system
        except Exception as e:
            print(f"An error occurred: {e}")
    else:
        print(f"Shortcut file {shortcut_path} not found")

def click_play():
    print(f"Looking for image at: {play_image}")
    if os.path.isfile(play_image):
        while True:
            try:
                play_loc = pyautogui.locateCenterOnScreen(play_image, confidence=0.8)
                if play_loc:
                    pyautogui.click(play_loc)
                    print("Play clicked")
                    time.sleep(3)
                    break
                else:
                    print("Play button not found on the screen, retrying...")
                    time.sleep(1)
            except ImageNotFoundException:
                print("Play image not found, retrying...")
                time.sleep(1)
    else:
        print(f"Image file {play_image} not found")

def select_ak():

            try:
                free_loc = pyautogui.locateCenterOnScreen(free_im,confidence=0.9)
                
 
                if free_loc:
                    pyautogui.click(free_loc)
                    print("Free champ selected")    
                    
            except ImageNotFoundException:
                print("image not found, retrying...")
                


            try:
                lock_loc = pyautogui.locateCenterOnScreen(lock_image, confidence=0.8)
                if lock_loc:
                    pyautogui.click(lock_loc)
                    print("Lock icon clicked")
                else:
                    
                    time.sleep(1)
            except ImageNotFoundException:
                time.sleep(0.2)
                
                


def find_match():
        while True:
            print(f"Looking for image at: {find_match_image}")
            try:
                find_match_loc = pyautogui.locateCenterOnScreen(find_match_image, confidence=0.8)
                if find_match_loc:
                    pyautogui.click(find_match_loc)
                    print("Find Match clicked")
                    break
                else:
                    time.sleep(1)
            except ImageNotFoundException:
                
                time.sleep(1)      


    
def select_bot_queue():
    print(f"Looking for image at: {botQ_image}")
    if os.path.isfile(botQ_image):
        while True:
            try:
                botQ_loc = pyautogui.locateCenterOnScreen(botQ_image, confidence=0.8)
                if botQ_loc:
                    pyautogui.click(botQ_loc)
                    print("Bot Queue clicked")
                    time.sleep(3)
                    break
                else:
                    
                    time.sleep(1)
            except ImageNotFoundException:
                
                time.sleep(1)

        print(f"Looking for image at: {noob_image}")
        while True:
            try:
                noob_loc = pyautogui.locateCenterOnScreen(noob_image, confidence=0.8)
                if noob_loc:
                    pyautogui.click(noob_loc)
                    time.sleep(3)
                    break
                else:
                    
                    time.sleep(1)
            except ImageNotFoundException:
                
                time.sleep(1)

        print(f"Looking for image at: {confirm_image}")
        while True:
            try:
                confirm_loc = pyautogui.locateCenterOnScreen(confirm_image, confidence=0.8)
                if confirm_loc:
                    pyautogui.click(confirm_loc)
                    print("Confirmation clicked")
                    time.sleep(3)
                    break
                else:
                
                    time.sleep(1)
            except ImageNotFoundException:
                
                time.sleep(1)


def accept_match():  
        try:
            accept_loc = pyautogui.locateCenterOnScreen(accept_image, confidence=0.8)
            if accept_loc:
                pyautogui.click(accept_loc)
                print("Match Accepted")
                time.sleep(1)
            else:
            
                time.sleep(1)
        except ImageNotFoundException:
            
            time.sleep(1)

def game_loading():
        try:
            location = pyautogui.locateCenterOnScreen(gold_image, confidence=0.8)
            if location:
                print("Game Loaded!")
                time.sleep(1)
                return True
            else:
                
                return False
        except ImageNotFoundException:
            
            return False
              

def inqueue():
    try:
        inqloc = pyautogui.locateCenterOnScreen(inQ_im, confidence=0.8)
        if inqloc:
            return True
        else :
            return False
    except Exception as e:
        
        return False  

def buy_smite():
    keyboard.press('p')
    keyboard.release('p')
    time.sleep(1)
    
    print(f"Looking for image at: {red_smite_image}")
    while True:
        try:
            smite_loc = pyautogui.locateCenterOnScreen(red_smite_image, confidence=0.8)
            if smite_loc:
                pyautogui.click(smite_loc, button='right')
                pyautogui.click(smite_loc, button='right')
                print("Red Smite Item bought")
                time.sleep(0.2)
                break
            else:
                
                time.sleep(1)
        except ImageNotFoundException:
            
            time.sleep(1)
    
    keyboard.press('p')
    keyboard.release('p')
    keyboard.press('y')
    keyboard.release('y')
    pyautogui.click(smite_loc,button='right')
    print("Shop closed")



def wander():
    screen_width, screen_height = pyautogui.size()  # Get screen resolution
    # Generate random coordinates within screen bounds
    right_side_start_x = screen_width // 2  # Start from the middle of the screen
    x = random.randint(right_side_start_x, screen_width - 100)
    y = random.randint(0, screen_height - 100)
    # Move to the random coordinates and perform a right-click
    pyautogui.moveTo(x, y, duration=1)  # Smooth movement over 1 second
    keyboard.press(Key.space)
    keyboard.release(Key.space)
    print(f"Moved to ({x}, {y}) and right-clicked")
    time.sleep(1)

def levelup():
    try:
        levelup_loc = pyautogui.locateCenterOnScreen(levelup_image, confidence=0.8)
        if levelup_loc:
            pyautogui.click(levelup_loc)  
        else:
            print("No level up available")
    except ImageNotFoundException:
        print("No image found for leveling up")
    

def nextgame():
    while True:
     try:
        next_loc = pyautogui.locateCenterOnScreen(next_game_image, confidence=0.8)
        if next_loc:
            pyautogui.click(next_loc)
            time.sleep(2.3)
            pyautogui.click(next_loc)
            time.sleep(2.3)

            break  
        else:
            print("Next game button not found")
     except ImageNotFoundException:
        print("Retrying to find continue picture")

def gamefinish():
    try:
        cont_loc = pyautogui.locateCenterOnScreen(cont_image, confidence=0.8)
        if cont_loc:
            
            return True
        else:
            return False
    except Exception as e:
        print(f"Game didnt finish yet")
        return False
def main():
    start_league()
    print("Please wait 32 Seconds for loading :D")
    click_play()
    select_bot_queue()
    find_match()
    
    while True:
            # Continuously monitor and accept matches if in queue
            while inqueue():
                accept_match()
                
            # Once out of queue, proceed with game actions
            select_ak()
            if game_loading():
                #buy_smite()
                while not gamefinish():
                  wander()
                  time.sleep(5)
                time.sleep(45)  
                levelup()
                time.sleep(1)
                levelup()
                time.sleep(1)
                detect_daily()
                nextgame()
                find_match()

            else:
                print("Game didnt start")    
                



if __name__ == "__main__":
    main()

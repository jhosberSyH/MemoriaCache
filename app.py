import flet
from flet import *
from datetime import datetime
import sqlite3

# Let's create the form class first so we can get some data
class FormContainer(UserControl):
    def __init__(self):
        #self.func = func
        super().__init__()

    def build(self):
        return Container(
            width=280,
            height=80,
            bgcolor="bluegrey500",
            opacity=0,
            border_radius=40,
            margin=margin.only(left=-20, right=-20),
            animate=animation.Animation(400, "decelerate"),
            animate_opacity=200,
            padding=padding.only(top=45, bottom=45),
            content=Column(
                horizontal_alignment=CrossAxisAlignment.CENTER,
                controls=[
                    TextField(
                        height=48,
                        width=255,
                        filled=True,
                        text_size=12,
                        border_color="transparent",
                        hint_text="Description...",
                        hint_style=TextStyle(size=11, color="black"),
                    ),
                    IconButton(content=Text("Add Task"))
                ]
            )
        )

def main(page: Page):
    page.horizontal_alignment = 'center'
    page.vertical_alignment = 'center'

    #function to show/hide form container
    def CreateToDoTask(e):
        #when we click the ADD...
        if form.height != 200:
            form.height, form.opacity = 200, 1
            form.update()
        else:
            form.height, form.opacity = 80, 0
            form.update()
        

    _main_column_ = Column(
        scroll="hidden",
        expand=True,
        alignment=MainAxisAlignment.START,
        controls=[
            Row(
                alignment=MainAxisAlignment.SPACE_BETWEEN,
                controls=[
                    #Some title stuff...
                    Text("To-Do Items", size=18, weight="bold",color="white"),
                    IconButton(
                        icons.ADD_CIRCLE_ROUNDED,
                        icon_size=18,
                        on_click=lambda e: CreateToDoTask(e),
                    )
                ]
            ),
            Divider(height=8, color="white24"),
        ]
    )

    #set up some bg and main container
    #The general UI will copy that of a mobile app
    page.add(
        #This is juts a bg container
        Container(
            width=1500,
            height=650,
            margin=10,
            bgcolor="bluegrey900",
            alignment=alignment.center,
            content=Row(
                alignment=MainAxisAlignment.CENTER,
                vertical_alignment=CrossAxisAlignment.CENTER,
                #Main container
                controls=[
                    Container(
                        width=280, 
                        height=600, 
                        bgcolor="#0f0f0f",
                        border_radius=40,
                        border=border.all(0.5,"white"),
                        padding=padding.only(top=35, left=20, right=20),
                        clip_behavior=ClipBehavior.HARD_EDGE, #clip contents to container
                        content=Column(
                            alignment=MainAxisAlignment.CENTER,
                            expand=True,
                            controls=[
                                #main column here...
                                _main_column_,
                                #form class here...
                                FormContainer(),
                            ]
                        )
                    )
                ]
            )
        )   
    )

    page.update()

    form = page.controls[0].content.controls[0].content.controls[1].controls[0]


if __name__ == "__main__":
    flet.app(target=main)
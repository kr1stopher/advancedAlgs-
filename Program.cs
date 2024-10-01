using System;
using System.ComponentModel.DataAnnotations;

namespace PolyInheritenceOverload {
   abstract class Shape { //abstract class: missing or incomplete implementation, meant to be used as a base class
      protected double width; 
      protected double length;

      public Shape (double len =1, double wid = 1){ //constructor with default args
         width = wid;
         length = len;
      }

      protected virtual double GetArea(){ //protected keyword allows a child class to access 
         Console.WriteLine("You need to specify a shape to get the area");
         return 0;
      }
      public abstract double GetPerimeter(); //abstract function has a missing implementation

   }

   class Rectangle : Shape {
      public Rectangle(double len=0, double wid=0) : base(len, wid) {} //Call the base constructor using the "base" keyword. 
      protected override double GetArea() { //polymorphism function overloading
         return length*width;
      }
      public override double GetPerimeter(){
         return length*2+width*2;
      }
      public static Rectangle operator+ (Rectangle r1, Rectangle r2) { //overloading the "+" operator to work with the rectangle class
         Rectangle rectangle = new Rectangle(r1.length + r2.length, r1.width+r2.width);
         return rectangle;
      }
   }

//isosceles (triangle version of the rectangle class)
   class Triangle : Shape {
      protected override double GetArea() { 
         return length*width*.5;
      }
      public override double GetPerimeter(){
         return Math.Pow((4*(length*length)+(width*width)+(width)),.5);
      }
   }

   class BecasueIHaveTo{
      public static void Main(){
         Rectangle r1 = new Rectangle(1,2);
         Rectangle r2 = r1+r1;;
         Console.WriteLine(r2.GetPerimeter());
      }
   }






}
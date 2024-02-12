/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_composition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:50 by lannur-s          #+#    #+#             */
/*   Updated: 2024/02/12 13:51:37 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// Base structure representing a shape
struct shape {
    int type;
};

// Structure representing a rectangle
struct rectangle {
//    struct shape base; // Composition: rectangle contains a shape
    int base;
    int width;
    int height;
};

// Structure representing a circle
struct circle {
    struct shape base; // Composition: circle contains a shape
    int radius;
};

// Function to print the type of shape
void print_type(struct shape *s) {
    switch (s->type) {
        case 1:
            printf("Rectangle\n");
            break;
        case 2:
            printf("Circle\n");
            break;
        case 5:        
            printf("Ha Ha Ha\n");
            break;
        default:
            printf("Unknown\n");
    }
}

int main() {
/*     struct rectangle rect = {{1}, 5, 3}; // Creating a rectangle
    struct circle cir = {{2}, 4};         // Creating a circle
 */
    struct rectangle rect;
    
    //rect.base.type = 1;
    rect.base = 1;
    rect.width = 5;
    rect.height = 3; // Creating a rectangle
    
    struct circle cir = {{2}, 4};         // Creating a circle


    print_type((struct shape *)&rect); // Print the type of rectangle
    print_type((struct shape *)&cir);  // Print the type of circle

    return 0;
}

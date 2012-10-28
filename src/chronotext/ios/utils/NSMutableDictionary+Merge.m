#import "NSMutableDictionary+Merge.h"

@implementation NSMutableDictionary (Merge)

+ (id) dictionaryWithObjectsFromDictionary:(NSDictionary*)otherDictionary withKeys:(id)firstKey, ...
{
    NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
    
    va_list keys;
    va_start(keys, firstKey);
    
    for (NSString *key = firstKey; key != nil; key = va_arg(keys, NSString*))
    {
        id object = [otherDictionary objectForKey:key];
        
        if (object)
        {
            [dictionary setObject:object forKey:key];
        }
    }
    
    va_end(keys);
    
    return dictionary;
}

- (void) addObjectsFromDictionary:(NSDictionary*)otherDictionary withKeys:(id)firstKey, ...
{
    va_list keys;
    va_start(keys, firstKey);
    
    for (NSString *key = firstKey; key != nil; key = va_arg(keys, NSString*))
    {
        [self setObject:[otherDictionary objectForKey:key] forKey:key];
    }
    
    va_end(keys);
}

@end

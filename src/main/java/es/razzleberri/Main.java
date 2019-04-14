package es.razzleberri;

import es.razzleberri.io.BedrockEntitySerializer;
import es.razzleberri.io.CraftStudioDeserializer;

import java.io.File;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class Main {
    
    public static void main(String... args) throws IOException {
        if (args.length < 2)
            exitWithError("Usage: java -jar <jar_path> <csjsmodel_path> <entity_path> [flags (r=replace)]");
    
        final File
            csFile = new File(args[0]),
            entityFile = new File(args[1]);
    
        Set<Character> flags = new HashSet<>(4);
        if (args.length > 2)
            for (char c : args[2].toCharArray())
                flags.add(c);
        
        if (!csFile.isFile())
            exitWithError(csFile + " must be a file!");
        if (entityFile.exists() && !flags.contains('r'))
            exitWithError(entityFile + " already exists!");
        
        long time = System.currentTimeMillis();
        CraftStudioModel csModel = new CraftStudioDeserializer().fromFile(csFile);
        BedrockEntityModel entityModel = CraftStudioToBedrockEntity.convert(csModel);
        new BedrockEntitySerializer().toFile(entityModel, entityFile);
        time = System.currentTimeMillis() - time;
        
        System.err.println("Done! (" + time + " ms)");
    }
    
    private static void exitWithError(String error) {
        System.err.println(error);
        System.exit(1);
    }
    
}
